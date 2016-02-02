# tinySASIAE

It is a really simple robot simulator that is to be used with Aversive++.
The robot is a 2 wheeled robot that has 2 motor, 2 encoders, and a communication port.

## Install

You only need Qt5 and qmake-qt5.
Here are the commands you need to download, compile, and install the simulator.

```
git clone https://github.com/astralien3000/tinySASIAE.git
cd tinySASIAE
qmake-qt5 tinySASIAE.pro
make
sudo make install
```

## Use

tinySASIAE only need a robot binary in the elf format.

``` 
tinySASIAE -r $ROBOT_ELF
```

## Develop a robot

You will need either the current development version or the v14.11 of Aversive++, [go there for more information](http://aversiveplusplus.com/download.html).
The development version and the old v14.11 have some differences in the API, so it is not compatible.

The example code in the tinySASIAE directory is to be used with v14.11.
