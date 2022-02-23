#pragma once
#include <fstream>

namespace MathLibrary
{
 class Number
 {
  double number = 0;
 public:
  Number() = default;
  Number(double a);
  Number& operator=(Number& c);
  // оператор сложения
  Number operator+(const Number& c);

  // оператор вычитания
  Number operator-(const Number& c);

  // оператор умножения
  Number operator*(const Number& c);

  // оператор деления
  Number operator/(const Number& c);

  double getValue();

  friend std::ostream& operator<< (std::ostream&, const Number&);
  friend std::istream& operator>> (std::istream&, Number&);

 };

 const Number ZERO(0);
 const Number ONE(1);

 Number create(double a);

}