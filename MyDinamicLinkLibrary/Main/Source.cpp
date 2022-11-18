#include <iostream>
#include "../MyDinamicLinkLibrary/MyLibrary.h"
using namespace std;

int main()
{
	int a, b, result;
	char c;
	cout << "Enter first value: ";
	cin >> a;
	cout << "Enter second value: ";
	cin >> b;
	cout << "Enter (+, -, /, *): ";
	cin >> c;
	switch (c)
	{
	case'*':
		result = Mult(a,b);
		break;
	case'+':
		result = Sum(a, b);
		break;
	case'-':
		result = Sub(a, b);
		break;
	case'/':
		result = Dev(a, b);
		break;

	}
	cout << "Result: " << a << c << b << '=' << result << endl;
	return 0;
}