#include "devices.hpp"

s32 le, re, lm, rm;

// Encoder devices
Encoder<s32> left_enc("leftEnc", &le);
Encoder<s32> right_enc("rightEnc", &re);

// Motor devices
Motor<s32> left_motor("leftMot", &lm);
Motor<s32> right_motor("rightMot", &rm);

// COMM
UartStream<0> io("io");
