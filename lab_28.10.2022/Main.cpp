#include <iostream>
#include <tchar.h>
using namespace std;


void Task1(_TCHAR str[])
{
	cout << "[Task1]\n";

	for (size_t i = 0; i < _tcslen(str); i++)
	{
		if (str[i] == _TEXT(" ")[0])
			str[i] = _TEXT("\t")[0];
	}
	wcout << str << endl << endl;
}

void Task2(const _TCHAR str[])
{
	cout << "[Task2]\n";

	size_t letters = 0;
	size_t numbers = 0;
	size_t symbols = 0;
	
	for (size_t i = 0; i < _tcslen(str); i++)
	{
		if (str[i] >= _TEXT("0")[0] && str[i] <= _TEXT("9")[0])
			numbers++;
		else if (
			(str[i] >= _TEXT("a")[0] && str[i] <= _TEXT("z")[0]) ||
			(str[i] >= _TEXT("A")[0] && str[i] <= _TEXT("Z")[0]) ||
			(str[i] >= _TEXT("А")[0] && str[i] <= _TEXT("Я")[0]) ||
			(str[i] >= _TEXT("а")[0] && str[i] <= _TEXT("я")[0])
			)
		{
			letters++;
		}
		else
		{
			symbols++;
		}
	}
	wcout << "Letter: " << letters << endl;
	wcout << "Numbers: " << numbers << endl;
	wcout << "Symbols: " << symbols << endl << endl;
}

void Task3(const _TCHAR str[])
{
	cout << "[Task3]\n";

	size_t word = 0;

	wcout << str << endl;

	for (size_t i = 0; i < _tcslen(str); i++)
	{
		if (str[i] != _TEXT(' '))
		{
			word++;
			do
			{
				i++;
			} while (i < _tcslen(str) && str[i] != ' ' && str[i] != '\t');
			i--;
		}
	}

	cout << "Words: " << word << endl << endl;
}



void Task5(const _TCHAR str[])
{
	cout << "[Task5]\n";

	const _TCHAR vowls[21] = _TEXT("АаЕеЁёИиОоУуЭэЮюЯяЫы");
	size_t vowl = 0;

	for (size_t i = 0; i < _tcslen(str); i++)
	{
		for (size_t j = 0; j < _tcslen(vowls); j++)
		{
			if (str[i] == vowls[j])
			{
				vowl++;
				break;
			}
		}
	}

	cout << "Vowl: " << vowl << endl << endl;
}

void Task6(const _TCHAR str[])
{
	cout << "[Task6]\n";
	
	bool check = true;

	size_t j = _tcslen(str) - 1;
	for (size_t i = 0; i  != j; i++, j--)
	{
		if (str[i] == _TEXT(" ")[0] || str[i] == _TEXT("\t")[0])
		{
			j--;
			continue;
		}
		if (str[j] == _TEXT(" ")[0] || str[j] == _TEXT("\t")[0])
		{
			i--;
			continue;
		}
		if (str[i] != str[j])
		{
			check = false;
			break;
		}
	}

	if (check)
		cout << "Is a Palendrom\n";
	else
		cout << "Is not a Palendrom\n";
	cout << endl;
}

void Task7( _TCHAR str[], size_t element)
{
	cout << "[Task7]\n";

	if (element < 1 || element - 1 >= _tcslen(str))
		return;
	else
	{
		element--;
		for (size_t i = element; i < _tcslen(str); i++)
			str[i] = str[i + 1];
	}
}

void Task8( _TCHAR str[], _TCHAR ch)
{
	for (size_t i = 0; i < _tcslen(str); i++)
	{
		if (str[i] == ch) 
		{
			for (size_t j = i; j < _tcslen(str); j++)
				str[j] = str[j + 1];
		}
	}
}

void Task9(_TCHAR str[], _TCHAR ch, size_t element)
{
	if (element < 1 || element - 1 > _tcslen(str))
		return;
	else
	{
		element--;
		for (int i = _tcslen(str); i > element; i--)
		{
			str[i] = str[i - 1];
		}
		str[element] = ch;
	}
}

int main()
{
	_TCHAR str[] = _TEXT("1vav_ _vav1");
	wcout << str << endl << endl;
	Task1(str);
	Task2(str);
	Task3(str);
	Task5(str);
	Task6(str);
	Task7(str, 11);
	wcout << str << endl << endl;
	Task8(str, _TEXT('1'));
	wcout << str << endl << endl;
	Task9(str, _TEXT('6'),10);
	wcout << str << endl << endl;
	return 0;
}

/*RESULT*/
/*
1vav_ _vav1

[Task1]
1vav_   _vav1

[Task2]
Letter: 6
Numbers: 2
Symbols: 3

[Task3]
1vav_   _vav1
Words: 2

[Task5]
Vowl: 0

[Task6]
Is a Palendrom

[Task7]
1vav_   _vav

vav_    _vav

vav_    _vav6
*/