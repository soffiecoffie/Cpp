#include "Utils.h"
#include <iostream>
#include <cassert>

//връща броя на цифрите на дадено число
int digits(int n)
{
	if (n == 0)	return 0;
	return 1 + digits(n / 10);
}

//връща истина ако подаденото число е нечетно
bool isOdd(int n) 
{
	return n % 2 != 0;
}

//извежда на екрана даден символ по даден брой пъти
std::ostream& printMany(const char* ch, size_t n, std::ostream& out)
{
	for (size_t i = 0; i < n; ++i)
	{
		out << ch;
	}
	return out;
}


//проверява дали празното място на подадения индекс в дадения низ се намира между думи
bool isSpaceBetweenWords(std::string str, size_t ind)
{
	assert(str[ind] == ' ');
	if (ind != str.size() - 1 && ind != 0) {
		return (str[ind - 1] != ' ') && (str[ind + 1] != ' ');
	}
	return false; //ако е първия или последния символ 
}
