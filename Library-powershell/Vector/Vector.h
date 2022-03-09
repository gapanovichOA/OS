#pragma once
#include <MathLibrary.h>
#include <cmath>
#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

namespace MathLibrary {
 class Vector {
 private:
  Number x;
  Number y;
 public:
  VECTOR_API Vector(Number x_, Number y_);
  VECTOR_API Vector& operator=(Vector& v);
  VECTOR_API Vector operator+(const Vector& v);
  VECTOR_API Number countR();
  VECTOR_API Number countPhi();
  VECTOR_API friend std::ostream& operator<< (std::ostream&, const Vector&);
  VECTOR_API friend std::istream& operator>> (std::istream&, Vector&);
 };
 const Vector ZERO_VECTOR(ZERO, ZERO);
 const Vector ONE_VECTOR(ONE, ONE);
}


