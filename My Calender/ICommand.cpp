#include "ICommand.h"

size_t ICommand::getMinNumberOfWords() const
{
	return getNumberOfWords();
}

size_t ICommand::getMaxNumberOfWords() const
{
	return getNumberOfWords();
}

//връща думата, която е num по ред в подадения низ str
std::string ICommand::getWord(size_t num, const std::string& str) const //validation if it has enough words to ask for the num one
{																		//doesn't work if its the last
	std::string result = str;
	size_t start = 0;
	size_t counter = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ') {
			if (num == 1) {
				result.erase(result.begin() + i, result.end()); //test
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

//връща низът, който се намира след даден номер на дума в даден низ
std::string ICommand::getStringAfterWord(size_t num, const std::string& str) const //validation if it has enough words to ask for the num one
{
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