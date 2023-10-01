#include <stdio.h>
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int main()
{
	std::string str;
	int cnt = 0;
	std::getline(std::cin,str);
	if (str.empty())
	{
		cout << "0";
		return 0;
	}
	cnt = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			cnt++;

	}
	if (str[0] == ' ')
		cnt--;
	if (str[str.length() - 1] == ' ')
		cnt--;

	std::cout << cnt;

	return 0;
}
