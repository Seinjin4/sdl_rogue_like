#pragma once

#include <iostream>

class Vector2
{
private:
  double x,y;

public:
  Vector2();
  Vector2(double x, double y);

  double get_x() const;
  double get_y() const;

  void set_x(double x);
  void set_y(double y);

  double magnitude() const;// return sqrt(x^2 + y^2)

  void normalize(); //Make magnitude 0 while keeping the angle
  void vector_floor(); //Round vector's values down
  void vector_ceil(); //Round vector's values up
  void vector_round(); //Rounds to closest integer

  void vector_ceil_abs(); //Rounds vector's values up from abs() perspective, negative - down, positive - up

  Vector2 operator + (const Vector2& v);
  Vector2 operator - (const Vector2& v);

  Vector2 operator * (const double& x);

  friend std::ostream& operator << (std::ostream& os, const Vector2& v);
};
