// MathClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// MathClient.cpp
// compile with: cl /EHsc MathClient.cpp /link MathLibrary.lib

#include <iostream>
#include "Vector.h"

using namespace MathLibrary;
int main()
{
Number a(3);
Number b(6);
Number c = create(8);
 std::cout << c<<std::endl;
 std::cout << a+b<<std::endl;
 std::cout << a-b<<std::endl;
 std::cout << a*b<<std::endl;
 std::cout << a/b<<std::endl;

 Vector v1(create(1), create(5));
 Vector v2(create(3),create(8));
 std::cout << v1 << std::endl;
 std::cout << v2 << std::endl;
 std::cout << v1 + v2 << std::endl;
 std::cout <<"phi=" <<v1.countPhi() << std::endl;
 std::cout <<"r=" <<v1.countR() << std::endl;
 return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
