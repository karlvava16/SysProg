#define MyDll_API extern "C" __declspec(dllexport)

#include "MyLibrary.h"


MyDll_API const double Pi = 3.1415;

void Test()
{
	std::cout << "Hello world!\n";
}

MyDll_API int fooInDll()
{
	int a = 100;
	return a;
}

MyDll_API int barInDll()
{
	return 0;
}

MyDll_API int Sum(int a, int b)
{
	return a + b;
}

MyDll_API int Mult(int a, int b)
{
	return a * b;
}

MyDll_API int Sub(int a, int b)
{
	return a - b;
}

MyDll_API int Dev(int a, int b)
{
	if (b != 0)
		return a / b;
	else
		return b;
}
