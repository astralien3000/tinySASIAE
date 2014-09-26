#include <aversive.hpp>

#include <device/eirbot2014/motor.hpp>
#include <device/eirbot2014/encoder.hpp>

#include <filter/pid_filter.hpp>
#include <filter/diff_filter.hpp>

#include <device/controller/motor_controller.hpp>
#include <device/controller/robot_controller.hpp>

#include <device/eirbot2014/odometer.hpp>

#include <system/scheduler.hpp>

s32 le;
s32 re;
s32 lm;
s32 rm;

PidFilter id = PidFilter::identity();

PidFilter left_pid;
PidFilter right_pid;

DiffFilter left_diff;
DiffFilter right_diff;

Encoder<s32> left_enc("leftEnc", &le);
Encoder<s32> right_enc("rightEnc", &re);
Motor<s32> left_motor("leftMot", &lm);
Motor<s32> right_motor("rightMot", &rm);

MotorController left_cmot(left_motor, left_enc, id, left_diff, left_pid);
MotorController right_cmot(right_motor, right_enc, id, right_diff, right_pid);

Odometer odo(right_enc, left_enc);

PidFilter dist_pid;
PidFilter angle_pid;

RobotController robot(right_cmot, left_cmot, odo, id, id, dist_pid, id, id, angle_pid);

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Aversive::init();

  left_pid.setGains(77,0,0);
  left_pid.setOutShift(6);

  right_pid.setGains(64,0,0);
  right_pid.setOutShift(6);

  left_diff.setDelta(1);
  right_diff.setDelta(1);

  dist_pid.setGains(10,0,0);
  dist_pid.setOutShift(0);

  angle_pid.setGains(50,0,0);
  angle_pid.setOutShift(0);
  
  odo.setAngleMultiplicator(2294);
  odo.setImpPerDeg(100000);

  Task t([]{
      robot.setValue(Vect<2, s32>(1000,0));
    });
  t.setRepeat();
  t.setPeriod(100000);
  
  Scheduler::instance().addTask(t);
  
  while(Aversive::sync()) {
  }
  
  return Aversive::exit();
}
