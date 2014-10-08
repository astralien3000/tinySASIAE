#include <aversive.hpp>

#include "devices.hpp"
#include "example.hpp"

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Aversive::init();

  Example::asserv_init();
  Example::scheduler_init();

  Example::asserv_goto(0, 45);
  
  while(Aversive::sync()) {
    if(Example::asserv_get_angle() == 45) {
      Example::asserv_goto(1000, 45);
    }

    if(abs(Example::asserv_get_dist() - 1000) < 2) {
      Example::asserv_goto(1000, 180);
    }

    if(Example::asserv_get_angle() == 180) {
      Example::asserv_goto(3000, 180);
    }

    io << "test " << Example::asserv_get_dist() << "\n";
  }
  
  return Aversive::exit();
}
