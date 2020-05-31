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

//връща думата, която е num по ред в подадения низ str
std::string getWord(size_t num, const std::string& str) //validation if it has enough words to ask for the num one
{
	std::string result = str;
	size_t start = 0;
	size_t counter = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ') {
			if (num == 1) {
				result.erase(result.begin() + i, result.end());
				return result;
			}
			++counter;
			if (counter == (num - 1)) start = i;
			else if (counter == num) {
				result.erase(result.begin() + i, result.end());
				result.erase(0, start + 1);

				return result;
			}
		}

		if (i == str.size() - 1) {
			result.erase(0, start + 1);
			return result;
		}
	}
}

//връща броя на думите в даден низ
size_t numOfWords(std::string s)
{
	size_t counter = 0;
	for (size_t i = 1; i < s.size() - 1; ++i)	 //така няма да брои празното място ако е в началото или края
	{
		if (s[i] == ' ') ++counter;
	}
	return counter + 1;
}