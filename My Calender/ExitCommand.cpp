#include "ExitCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
ExitCommand::ExitCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ExitCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата exit */
void ExitCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->exit();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string ExitCommand::toString() const
{
	return "exit";
}
