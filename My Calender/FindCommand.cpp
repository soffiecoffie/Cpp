#include "FindCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
FindCommand::FindCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t FindCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата find */
void FindCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		input = getStringAfterWord(1, input);
		s->find(input.c_str());
		std::cout << "Successfully executed find <string> command!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string FindCommand::toString() const
{
	return "find";
}
