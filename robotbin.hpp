#ifndef ROBOTBIN_HPP
#define ROBOTBIN_HPP

#include <QObject>
#include <QString>
#include <QProcess>

#include "robot.hpp"
#include "physics.hpp"

class RobotBin : public QObject
{
    Q_OBJECT
public:
    explicit RobotBin(QString path);
    virtual ~RobotBin();

signals:

public slots:
    void onEngineUpdate();
    void onRobotInput();

protected:
    void killProc();

private:
    Physics _engine;
    QProcess _interface;

    bool _left_encoder_enabled;
    bool _right_encoder_enabled;

public:
    const Robot& getRobot(void) const {
      return _engine.getRobot();
    }
};

#endif // ROBOTBIN_HPP
