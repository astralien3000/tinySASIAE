#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include "devices.hpp"
#include "control.hpp"

namespace Example {

  extern PidFilter id;

  extern PidFilter left_pid;
  extern PidFilter right_pid;
  
  extern DiffFilter left_diff;
  extern DiffFilter right_diff;
  
  extern MotorController left_cmot;
  extern MotorController right_cmot;
  
  extern Odometer odo;
  
  extern PidFilter dist_pid;
  extern PidFilter angle_pid;

  extern RobotController robot;

  void asserv_init(void);

  extern u32 dist;
  extern u32 angle;

  void asserv_goto(u32 d, u32 a);

  u32 asserv_get_angle(void);

  u32 asserv_get_dist(void);

  void control_task(void);

  void scheduler_init(void);

}

#endif//EXAMPLE_HPP
