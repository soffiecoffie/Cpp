#include "CmdValidator.h"

bool CmdValidator::validateCommand(const ICommand* ptr, std::string str)
{
	size_t wordsNumInStr = getNumOfWords(str);
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
