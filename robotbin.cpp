#include "robotbin.hpp"

//#include <QException>
#include <stdexcept>

#include <QStringList>
#include <QDebug>
#include <stdint.h>

#include <iostream>

#include <QCoreApplication>

static const char *const binPath = "robot/robot_sasiae.elf";
static const double encCoef = 100.;
static const double timeCoef = 1000000.;
static const int mainLoopIteration = 10;
static const double leftMotCoef = 1.;
static const double rightMotCoef = 1.2;

// Device initialisation messages
static const char *const leftEncInit = "D leftEnc init";
static const char *const rightEncInit = "D rightEnc init";
static const char *const ioInit = "D io init";

// From SASIAE to robot code messages
static const char *const leftEncMsg = "D leftEnc value %1";
static const char *const rightEncMsg = "D rightEnc value %1";
static const char *const syncMsg = "T %1 %2";

// From robot code to SASIAE messages
static const char *const syncMsg2 = "T";
static const char *const deviceMsg = "D";
static const char *const leftMotName = "leftMot";
static const char *const rightMotName = "rightMot";
static const char *const ioName = "io";
static const char *const valueMsg = "value";

// Generic messages
static const char *const stopMsg = "S";

RobotBin::RobotBin(QString path) :
    QObject(NULL),
    _left_encoder_enabled(false), _right_encoder_enabled(false)
{
    _interface.start(path, QStringList());
    if(!_interface.waitForStarted()) {
        qDebug() << "Could not start robot's code with path: " << path;
        throw std::runtime_error("");
    }

    _interface.connect(&_interface, SIGNAL(readyRead()), this, SLOT(onRobotInput()));
    _engine.getTimer().connect(&_engine.getTimer(), SIGNAL(timeout()), this, SLOT(onEngineUpdate()));
}

RobotBin::~RobotBin()
{
    if(_interface.state() != QProcess::NotRunning)
    {
        killProc();
    }
}

void RobotBin::onEngineUpdate()
{
  if(_left_encoder_enabled)  {
      _interface.write(QString(leftEncMsg).arg(static_cast<int32_t>(encCoef * _engine.getRobot().left_encoder)).toLocal8Bit().append("\n"));
  }

  if(_right_encoder_enabled) {
      _interface.write(QString(rightEncMsg).arg(static_cast<int32_t>(encCoef * _engine.getRobot().right_encoder)).toLocal8Bit().append("\n"));
  }

  _interface.write(QString(syncMsg).arg(static_cast<uint32_t>(timeCoef * _engine.getTime())).arg(mainLoopIteration).toLocal8Bit().append("\n"));
}

void RobotBin::onRobotInput()
{
    while(_interface.canReadLine()) {
        QString line = _interface.readLine(1024);
        QStringList words = line.remove('\n').split(" ");

        if(line == leftEncInit)
        {
            qDebug() << "Left Encoder initialized";
            _left_encoder_enabled = true;
        }
        else if(line == rightEncInit)
        {
            qDebug() << "Right Encoder initialized";
            _right_encoder_enabled = true;
        }
        else if(line == ioInit)
        {
            // NOTHING TO DO
        }
        else if(words[0] == QString(syncMsg2))
        {
            // NOTHING TO DO
        }
        else if(words[0] == QString(deviceMsg) && words[2] == QString(valueMsg))
        {
            double speed = words[3].toDouble();
            if(words[1] == QString(leftMotName))
            {
                _engine.getRobot().left_speed = leftMotCoef * speed;
            }
            else if(words[1] == QString(rightMotName))
            {
                _engine.getRobot().right_speed = rightMotCoef * speed;
            }
            else if(words[1] == QString(ioName)) {
                std::cout << (char)words[3].toInt();
            }
            else
            {
                // unknown device, skip
            }
        }
        else
        {
            // unrecognized message, skip
        }
    }
}

void RobotBin::killProc()
{
    _interface.kill();
    _interface.waitForFinished();
}
