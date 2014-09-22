#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include <QObject>
#include "robot.hpp"

class PhysicsEngine : public QObject
{
  Q_OBJECT

private:
  Robot& _robot;

public:
  PhysicsEngine(Robot& robot);

public slots:
  void update(void);
};

#endif // PHYSICSENGINE_HPP
