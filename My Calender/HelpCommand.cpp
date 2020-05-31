#include "HelpCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
HelpCommand::HelpCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t HelpCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата help */
void HelpCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->help();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string HelpCommand::toString() const
{
	return "help";
}
