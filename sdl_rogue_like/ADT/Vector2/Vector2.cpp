#include "Vector2.h"
#include <iostream>
#include <cmath>

 Vector2::Vector2()
 {
   this->x = 0;
   this->y = 0;

 }

 Vector2::Vector2(double x, double y)
 {
   this->x = x;
   this->y = y;
 }

 double Vector2::get_x() const
 {
   return x;
 }

 double Vector2::get_y() const
 {
   return y;
 }

 void Vector2::set_x(double x)
 {
   this->x = x;
 }

 void Vector2::set_y(double y)
 {
   this->y = y;
 }

 void Vector2::vector_floor()
 {
   set_x(floor(this->x));
   set_y(floor(this->y));
 }

 void Vector2::vector_ceil()
 {
   set_x(ceil(this->x));
   set_y(ceil(this->y));
 }

 void Vector2::vector_round()
 {
   set_x(round(this->x));
   set_y(round(this->y));
 }

 void Vector2::vector_ceil_abs()
 {
   if(this->x > 0)
   {
     set_x(ceil(this->x));
   }
   else
   {
     set_x(floor(this->x));
   }

   if(this->y > 0)
   {
     set_y(ceil(this->y));
   }
   else
   {
     set_y(floor(this->y));
   }
 }

 void Vector2::normalize()
 {
   double mag = this->magnitude();
   set_x(this->x / mag);
   set_y(this->y / mag);
 }

 double Vector2::magnitude() const
 {
   return sqrt(x*x + y*y);
 }



Vector2 Vector2::operator + (const Vector2& v)
{
  Vector2 vec1;
  vec1.set_x(this->get_x() + v.get_x());
  vec1.set_y(this->get_y() + v.get_y());
  return vec1;
}

Vector2 Vector2::operator - (const Vector2& v)
{
 Vector2 vec1;
 vec1.set_x(this->get_x() - v.get_x());
 vec1.set_y(this->get_y() - v.get_y());
 return vec1;
}

Vector2 Vector2::operator * (const double & x)
{
 Vector2 vec1;
 vec1.set_x(this->get_x() * x);
 vec1.set_y(this->get_y() * x);
 return vec1;
}

std::ostream & operator << (std::ostream &os, const Vector2 &v)
{
  os<<"( " << v.get_x() << " , " << v.get_y() << " )";
  return os;

}
