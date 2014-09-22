#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <QObject>
#include "robot.hpp"

class PhysicsEngine : public QObject
{
  Q_OBJECT

private:
  Robot& _robot;
  double _time;

public:
  PhysicsEngine(Robot& robot);

  double getTime(void);

public slots:
  void update(void);
};

#endif // PHYSICSENGINE_HPP
