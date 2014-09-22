#include "robotbin.hpp"

#include <QException>
#include <QStringList>
#include <stdint.h>

static const char *const binPath = "./robot_sasiae.elf";
static const double encCoef = 1.;
static const double timeCoef = 1.;
static const int mainLoopIteration = 10;
static const double leftMotCoef = 1.;
static const double rightMotCoef = 1.;

// From SASIAE to robot code messages
static const char *const leftEncMsg = "D leftEnc value %1";
static const char *const rightEncMsg = "D rightEnc value %1";
static const char *const syncMsg = "T %1 %2";

// From robot code to SASIAE messages
static const char *const syncMsg2 = "T";
static const char *const deviceMsg = "D";
static const char *const leftMotName = "leftMot";
static const char *const rightMotName = "rightMot";
static const char *const valueMsg = "value";

// Generic messages
static const char *const stopMsg = "S";

RobotBin::RobotBin(Robot& robot, const PhysicsEngine& engine, QObject *parent) :
    QObject(parent), _robot(robot), _engine(engine)
{
    _proc.start(binPath, QStringList());
    if(!_proc.waitForStarted()) {
        throw QException();
    }
}

RobotBin::~RobotBin()
{
    if(_proc.state() != QProcess::NotRunning)
    {
        killProc();
    }
}

void RobotBin::update()
{
    _proc.write(QString(leftEncMsg).arg(static_cast<int32_t>(encCoef * _robot.left_encoder)).toLocal8Bit().append("\n"));
    _proc.write(QString(rightEncMsg).arg(static_cast<int32_t>(encCoef * _robot.right_encoder)).toLocal8Bit().append("\n"));
    _proc.write(QString(syncMsg).arg(static_cast<u_int32_t>(timeCoef * _engine.getTime())).arg(mainLoopIteration).toLocal8Bit().append("\n"));

    QString line;
    while((line = readLineFromProc()) != QString() && line != QString(syncMsg2) && line != QString(stopMsg))
    {
        QStringList words = line.split(" ");
        if(words.length() != 4)
        {
            killProc();
            throw QException();
        }

        if(words[0] == QString(deviceMsg) && words[2] == QString(valueMsg))
        {
            double speed = words[3].toDouble();
            if(words[1] == QString(leftMotName))
            {
                _robot.left_speed = leftMotCoef * speed;
            }
            else if(words[1] == QString(rightMotName))
            {
                _robot.right_speed = rightMotCoef * speed;
            }
            else
            {
                killProc();
                throw QException();
            }
        }
        else
        {
            killProc();
            throw QException();
        }
    }
}

QString RobotBin::readLineFromProc()
{
    QString line;
    char c = 0;

    if(!_proc.getChar(&c)) {
        _proc.waitForReadyRead();
    }
    else {
        line.append(QChar(c));
    }

    while(_proc.getChar(&c) && c != '\n') {
        line.append(QChar(c));
    }

    if(c == '\n') {
        return line;
    }
    else {
        // Problem
        return QString();
    }
}

void RobotBin::killProc()
{
    _proc.kill();
    _proc.waitForFinished();
}
