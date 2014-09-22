#include "robotbin.hpp"

#include <QException>
#include <QStringList>

static const char *const binPath = "./robot_sasiae.elf";
static const double encCoef = 1.;
static const double timeCoef = 1.;
static const int mainLoopIteration = 10;
static const double leftMotCoef = 1.;
static const double rightMotCoef = 1.;

// From SASIAE to robot code messages
static const char *const leftEncMsg = "D leftEnc value %1\n";
static const char *const rightEncMsg = "D rightEnc value %1\n";
static const char *const syncMsg = "T %1 %2\n";

// From robot code to SASIAE messages
static const char *const syncMsg2 = "T\n";
static const char *const deviceMsg = "D";
static const char *const leftMotName = "leftMot";
static const char *const rightMotName = "rightMot";
static const char *const valueMsg = "value";

// Generic messages
static const char *const stopMsg = "S\n";

RobotBin::RobotBin(Robot& robot, const PhysicsEngine& engine, QObject *parent) :
    QObject(parent), _robot(robot), _engine(engine)
{
    _proc.start(binPath, QStringList());
    if(!_proc.waitForStarted()) {
        throw QException();
    }
}

void RobotBin::update()
{
    _proc.write(QString(leftEncMsg).arg(static_cast<int>(encCoef * _robot.left_encoder)).toLocal8Bit());
    _proc.write(QString(rightEncMsg).arg(static_cast<int>(encCoef * _robot.right_encoder)).toLocal8Bit());
    _proc.write(QString(syncMsg).arg(static_cast<int>(timeCoef * _engine.getTime())).arg(mainLoopIteration).toLocal8Bit());

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
            double speed = static_cast<double>(words[3].toInt());
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
        /*
        killProc();
        */
        return QString();
    }
}

void RobotBin::killProc()
{
    _proc.kill();
    _proc.waitForFinished();
}
