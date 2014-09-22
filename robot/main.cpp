#include <aversive.hpp>

#include <device/eirbot2014/motor.hpp>
#include <device/eirbot2014/encoder.hpp>

s32 le;
s32 re;
s32 lm;
s32 rm;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Aversive::init();
  
  Encoder<s32> leftEnc("leftEnc", &le);
  Encoder<s32> rightEnc("rightEnc", &re);
  Motor<s32> leftMotor("leftMot", &lm);
  Motor<s32> rightMotor("rightMot", &rm);

  leftMotor.setValue(128);
  rightMotor.setValue(128);
  
  while(Aversive::sync()) {
    if(leftEnc.getValue() >= 15) {
      leftMotor.setValue(0);
    }
    if(rightEnc.getValue() >= 15) {
      rightMotor.setValue(0);
    }
  }
  
  return Aversive::exit();
}
