#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>



using namespace std;

int main()
{
	wifstream file;
	cout << "Enter file name: ";
	wstring str = L"File.txt";
	getline(wcin, str);
	file.open(str);

	if (!file.is_open())
	{
		return -1;
	}

	map<int, int> m;
	int sum = 0;

	bool check = true;

	while (!file.eof())
	{
		file >> str;
		for (auto it = m.begin(); it != m.end(); it++)
		{
			if (it->first == _wtoi(str.c_str()))
			{
				// увеличиваем значение
				it->second++;
				check = false;
				break;
			}
		}
		if (check)
		{
			m.insert({ _wtoi(str.c_str()) , 1});
		}
		else
		{
			check = true;
		}
	}

	for (auto it = m.begin(); it != m.end(); it++)
	{
		sum += it->second;
	}

	cout << endl;
	for (auto it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "\t\t\t" << it->second << endl;
	}
	cout << endl;
	cout << "Sum: " << sum << endl << endl;

	system("pause");

	return 0;
}