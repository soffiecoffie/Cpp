#include "ICommand.h"

/** @brief виртуална функция, която връща броя на думите, които са необходими за дадена команда */
size_t ICommand::getMinNumberOfWords() const
{
	return getNumberOfWords();
}

/** @brief виртуална функция, която връща броя на думите, които са необходими за дадена команда */
size_t ICommand::getMaxNumberOfWords() const
{
	return getNumberOfWords();
}
