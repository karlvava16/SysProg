#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

typedef int (*FOO_IN_DLL)(int a, int b);

int main()
{
    HINSTANCE hInstLib = LoadLibrary(TEXT("MyDinamicLinkLibrary.dll"));

    if (hInstLib == NULL)
    {
        cout << "Can`t load library MyDinamicLinkLibrary.dll" << endl;
        return 0;
    }

	
	FOO_IN_DLL func;
	int a, b, result = 0;
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
		func = (FOO_IN_DLL)GetProcAddress(hInstLib, "Mult");
		result = func(a, b);
		break;
	case'+':
		func = (FOO_IN_DLL)GetProcAddress(hInstLib, "Sum");
		result = func(a, b);
		break;
	case'-':
		func = (FOO_IN_DLL)GetProcAddress(hInstLib, "Sub");
		result = func(a, b);
		break;
	case'/':
		func = (FOO_IN_DLL)GetProcAddress(hInstLib, "Div");
		result = func(a, b);
		break;

	}
	cout << "Result: " << a << c << b << '=' << result << endl;

    FreeLibrary(hInstLib);
}