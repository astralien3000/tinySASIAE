#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include "robot.hpp"

#include <QObject>
#include <QTimer>

class Physics : public QObject
{
  Q_OBJECT

private:
  Robot _robot;
  double _time;
  QTimer _timer;

public:
  Physics(void);

public:
  inline double getTime(void) const {
    return _time;
  }

  inline QTimer& getTimer(void) {
    return _timer;
  }

  inline Robot& getRobot(void) {
    return _robot;
  }

  inline const Robot& getRobot(void) const {
    return _robot;
  }

public slots:
  void update(void);
};

#endif // PHYSICSENGINE_HPP
