#ifndef DEVICES_HPP
#define DEVICES_HPP

#include <device/eirbot2014/motor.hpp>
#include <device/eirbot2014/encoder.hpp>

#include <device/stream/uart_stream.hpp>

// Encoder devices
extern Encoder<s32> left_enc;
extern Encoder<s32> right_enc;

// Motor devices
extern Motor<s32> left_motor;
extern Motor<s32> right_motor;

// COMM
extern UartStream<0> io;

#endif//DEVICES_HPP
