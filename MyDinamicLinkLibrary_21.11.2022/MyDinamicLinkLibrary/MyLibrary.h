#pragma once
#include <iostream>

#ifndef MyDll_API
#define MyDll_API extern "C" __declspec(dllimport)
#endif

void Test();
MyDll_API int fooInDll();
MyDll_API int barInDll();
MyDll_API int Sum(int a, int b);
MyDll_API int Mult(int a, int b);
MyDll_API int Sub(int a, int b);
MyDll_API int Dev(int a, int b);



MyDll_API const double Pi;