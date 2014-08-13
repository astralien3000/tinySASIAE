#ifndef ROBOT_HPP
#define ROBOT_HPP

struct Robot {
  double width;

  double x;
  double y;
  double angle;
  
  double left_speed;
  double right_speed;

  double left_encoder;
  double right_encoder;
};

#endif//ROBOT_HPP
