#include "CmdValidator.h"
#include "Utils.h"

//връща истина ако командата е валидна
bool CmdValidator::validateCommand(const ICommand* ptr, std::string str)
{
	size_t wordsInStr = numOfWords(str);
	if (wordsInStr <= ptr->getMaxNumberOfWords() && wordsInStr >= ptr->getMinNumberOfWords()) {
		if (wordsInStr > 1) {
			if (ptr->toString() == getWord(1, str)) {
				return true;
			}
		}
		else return ptr->toString() == str;
	}
	return false;
}