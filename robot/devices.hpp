#ifndef DEVICES_HPP
#define DEVICES_HPP

#include <device/eirbot2014/motor.hpp>
#include <device/eirbot2014/encoder.hpp>

#include <device/stream/uart_stream.hpp>

// Dummy variables
// used by memory-bound devices
s32 le;
s32 re;
s32 lm;
s32 rm;

// Encoder devices
Encoder<s32> left_enc("leftEnc", &le);
Encoder<s32> right_enc("rightEnc", &re);

// Motor devices
Motor<s32> left_motor("leftMot", &lm);
Motor<s32> right_motor("rightMot", &rm);

// COMM
UartStream<0> io("io");

#endif//DEVICES_HPP
