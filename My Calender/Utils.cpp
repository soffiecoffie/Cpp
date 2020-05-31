#include "Utils.h"
#include <cassert>

/** @brief връща броя на думите в даден низ */
size_t getNumOfWords(std::string s) {
	size_t counter = 0;
	for (size_t i = 1; i < s.size() - 1; ++i)	 //така няма да брои празното място ако е в началото или края
	{
		if (s[i] == ' ') ++counter;
	}
	return counter + 1;
}

/** @brief връща първата дума от даден низ */
std::string getFistWord(std::string s)
{
	std::string result = s;
	result.erase(getFirstSpaceInd(result), result.size() - 1);
	return result;
}

/** @brief връща индекса на първото срещнато празно място */
size_t getFirstSpaceInd(std::string s)
{
	for (size_t i = 1; i < s.size() - 1; ++i)
	{
		if (s[i] == ' ') return i;
	}
	return s.size() + 1; //за командите които са от една дума само
}

/** @brief връща думата, която е n-та по ред в подадения низ */
std::string getWord(size_t num, const std::string& str)
{
	assert(getNumOfWords(str) >= num);
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

/** @brief връща низа, който се намира след даден номер на дума в даден низ */
std::string getStringAfterWord(size_t num, const std::string& str)  
{
	assert(getNumOfWords(str) > num);
	std::string result = str;
	size_t counter = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ') {
			++counter;
			if (counter == num) {
				result.erase(0, i + 1);
			}
		}
	}
	return result;
}
