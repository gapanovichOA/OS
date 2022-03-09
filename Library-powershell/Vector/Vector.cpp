#include "Vector.h"


namespace MathLibrary {
 Vector::Vector(Number x_, Number y_) {
  x = x_;
  y = y_;
 }
 Vector& Vector::operator=(Vector& v) {
  x = v.x;
  y = v.y;
  return (*this);
 }
 Vector Vector::operator+(const Vector& v) {
  return Vector(x + v.x, y + v.y);
 }
 Number Vector::countR() {
  return Number(std::sqrt(x.getValue()*x.getValue()+y.getValue()*y.getValue()));
 }
 Number Vector::countPhi() {
  return Number(asin(y.getValue()/this->countR().getValue()));
 }
 // перегрузка оператора <<
 std::ostream& operator<< (std::ostream& out, const Vector& v)
 {
  out << "("<<v.x<<","<<v.y<<")";
  return out;
 }

 // перегрузка оператора >>
 std::istream& operator>> (std::istream& in, Vector& v)
 {
  in >> v.x>>v.y;
  return in;
 }
}