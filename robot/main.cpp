#include <aversive.hpp>

#include "devices.hpp"
#include "control.hpp"

#include "example.hpp"

#include <iostream>

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Aversive::init();

  example::asserv_init();
  example::scheduler_init();

  example::asserv_goto(0, 45);
  
  while(Aversive::sync()) {
    if(example::asserv_get_angle() == 45) {
      example::asserv_goto(1000, 45);
    }

    if(abs(example::asserv_get_dist() - 1000) < 2) {
      example::asserv_goto(1000, 180);
    }

    if(example::asserv_get_angle() == 180) {
      example::asserv_goto(3000, 180);
    }

    io << "test " << example::asserv_get_dist() << "\n";
  }
  
  return Aversive::exit();
}
