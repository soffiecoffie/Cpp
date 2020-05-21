#include "CmdValidator.h"

size_t CmdValidator::numOfWords(std::string s)
{
	size_t counter = 0;
	for (size_t i = 1; i < s.size() - 1; ++i)	 //така няма да брои празното място ако е в началото или края
	{
		if (s[i] == ' ') ++counter;
	}
	return counter + 1;
}

std::string CmdValidator::getFistWord(std::string s)
{
	std::string result = s;
	result.erase(getFirstSpaceInd(result), result.size() - 1);
	return result;
}

size_t CmdValidator::getFirstSpaceInd(std::string s)
{
	for (size_t i = 1; i < s.size() - 1; ++i)
	{
		if (s[i] == ' ') return i;
	}
	return s.size() + 1; //за командите които са от една дума само
}

bool CmdValidator::validateCommand(const ICommand* ptr, std::string str)
{
	size_t wordsNumInStr = numOfWords(str);
	if (wordsNumInStr <= ptr->getMaxNumberOfWords() && wordsNumInStr >= ptr->getMinNumberOfWords()) {
		if (wordsNumInStr > 1) {
			if (ptr->toString() == getFistWord(str)) {
				return true;
			}
		}
		else return ptr->toString() == str;
	}
	return false;
}
