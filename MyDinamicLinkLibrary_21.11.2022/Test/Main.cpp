#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

typedef int (*FOO_IN_DLL)();

int main()
{
    HINSTANCE hInstLib = LoadLibrary(TEXT("MyDinamicLinkLibrary.dll"));

    if (hInstLib == NULL)
    {
        cout << "Can`t load library MyDinamicLinkLibrary.dll" << endl;
        return 0;
    }

  

    const double* pPi = (const double*)GetProcAddress(hInstLib, "Pi");
    cout << "Pi: " << *pPi << endl;


    FOO_IN_DLL fooInDll = (FOO_IN_DLL)GetProcAddress(hInstLib, "fooInDll");

    if (fooInDll == NULL)
    {
        cout << "Can`t load function fooInDll" << endl;
    }
    else
    {
        cout << "fooInDll: " << fooInDll() << endl;
    }

	FOO_IN_DLL func;

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
		FOO_IN_DLL Mult = (FOO_IN_DLL)GetProcAddress(hInstLib, "Mult");
		result = Mult(a, b);
		break;
	case'+':
		func = (FOO_IN_DLL)GetProcAddress(hInstLib, "Mult");
		result = func(a, b);
		break;
	case'-':
		result = Sub(a, b);
		break;
	case'/':
		result = Dev(a, b);
		break;

	}
	cout << "Result: " << a << c << b << '=' << result << endl;

	FreeLibrary(hInstLib);


	return 0;
}