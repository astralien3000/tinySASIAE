# tinySASIAE

It is a really simple robot simulator that is to be used with Aversive++.
The robot is a 2 wheeled robot that has 2 motor, 2 encoders, and a communication port.

## Install

You only need Qt5 and qmake-qt5.
Here are the commands you need to download, compile, and install the simulator.

```bash
git clone https://github.com/astralien3000/tinySASIAE.git
cd tinySASIAE
qmake-qt5 tinySASIAE.pro
make
sudo make install
```

## Use

tinySASIAE only need a robot binary in the elf format.

```bash
tinySASIAE -r $ROBOT_ELF
```

## Develop a robot

You will need either the current development version or the v14.11 of Aversive++, [go there for more information](http://aversiveplusplus.com/download.html).
The development version and the old v14.11 have some differences in the API, so it is not compatible.

The example code in the tinySASIAE directory is to be used with v14.11.

### Devices to link with the simulator

The SASIAE protocol is quite simple, you just need the name of a Device to use it.
Here are the available devices : 

#### Encoders (input s32)
 - leftEnc
 - rightEnc

#### Motors (output s32)
 - leftMot
 - rightMot

#### Communication (stream)
 - io
 
### Example code

#### v14.11

```c++
#include <device/eirbot2014/motor.hpp>
#include <device/eirbot2014/encoder.hpp>
#include <device/stream/uart_stream.hpp>

s32 le, re, lm, rm;

// Encoder devices
Encoder<s32> left_enc("leftEnc", &le);
Encoder<s32> right_enc("rightEnc", &re);

// Motor devices
Motor<s32> left_motor("leftMot", &lm);
Motor<s32> right_motor("rightMot", &rm);

// COMM
UartStream<0> io("io");
```

#### current version

```c++
#include <device/sasiae/motor.hpp>
#include <device/sasiae/encoder.hpp>
#include <stream/sasiae/stream.hpp>

using namespace Device::SASIAE;
using namespace Stream::SASIAE;

// Encoder devices
Encoder left_enc("leftEnc");
Encoder right_enc("rightEnc");

// Motor devices
Motor left_motor("leftMot");
Motor right_motor("rightMot");

// COMM
Stream io("io");
```
