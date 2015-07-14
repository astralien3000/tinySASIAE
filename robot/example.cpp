#include "example.hpp"

namespace Example {

  PidFilter id = PidFilter::identity();

  PidFilter left_pid;
  PidFilter right_pid;
  
  DiffFilter left_diff;
  DiffFilter right_diff;
  
  MotorController left_cmot(left_motor, left_enc, id, left_diff, left_pid);
  MotorController right_cmot(right_motor, right_enc, id, right_diff, right_pid);
  
  Odometer odo(right_enc, left_enc);
  
  PidFilter dist_pid;
  PidFilter angle_pid;

  RobotController robot(right_cmot, left_cmot, odo, id, id, dist_pid, id, id, angle_pid);

  void asserv_init(void) {
    // Motor control
    left_pid.setGains(77,0,0);
    left_pid.setOutShift(6);
    
    right_pid.setGains(64,0,0);
    right_pid.setOutShift(6);
    
    left_diff.setDelta(1);
    right_diff.setDelta(1);
    
    // Robot control
    dist_pid.setGains(10,1,0);
    dist_pid.setMaxIntegral(100);
    dist_pid.setOutShift(0);
    
    angle_pid.setGains(50,0,0);
    angle_pid.setOutShift(0);
    
    odo.setAngleMultiplicator(2294);
    odo.setImpPerDeg(100000);
  }
  

  u32 dist = 0;
  u32 angle = 0; 

  void asserv_goto(u32 d, u32 a) {
    dist = d;
    angle = a;
  }

  u32 asserv_get_angle(void) {
    return odo.angle();
  }

  u32 asserv_get_dist(void) {
    return odo.distance();
  }

  void control_task(void) {
    robot.setValue(Vect<2, s32>(dist,angle));
  }

  void scheduler_init(void) {
    Task t(control_task);
    t.setRepeat();
    t.setPeriod(100000);
    
    Scheduler<DefaultSchedulerConfig>::instance().addTask(t);
  }

}
