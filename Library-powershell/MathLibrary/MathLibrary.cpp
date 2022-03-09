// MathLibrary.cpp
// compile with: cl /c /EHsc MathLibrary.cpp
// post-build command: lib MathLibrary.obj

#include "MathLibrary.h"

namespace MathLibrary
{
 Number::Number(double a) {
  number = a;
 }
 Number& Number::operator=(Number& c)
 {
  number = c.number;
  return (*this);
 }
 // оператор сложения
 Number Number::operator+(const Number& c)
 {
  return Number(number + c.number);
 }

 // оператор вычитания
 Number Number::operator-(const Number& c)
 {
  return Number(number - c.number);
 }

 // оператор умножения
 Number Number::operator*(const Number& c)
 {
  return Number(number * c.number);
 }

 // оператор деления
 Number Number::operator/(const Number& c)
 {
  return Number(number / c.number);
 }

 double Number::getValue() {
  return number;
 }

 Number create(double a) {
  return Number(a);
 }

 // перегрузка оператора <<
 std::ostream& operator<< (std::ostream& out, const Number& c)
 {
  out << c.number;
  return out;
 }

 // перегрузка оператора >>
 std::istream& operator>> (std::istream& in, Number& c)
 {
  in >> c.number;
  return in;
 }
}