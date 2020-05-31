#include "ICommand.h"

/** @brief виртуална функция, която връща минималният брой на думите, които са необходими за дадена команда */
size_t ICommand::getMinNumberOfWords() const
{
	return getNumberOfWords();
}

/** @brief виртуална функция, която връща максималният брой на думите, които съставят дадена команда */
size_t ICommand::getMaxNumberOfWords() const
{
	return getNumberOfWords();
}
