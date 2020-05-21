#include "HelpCommand.h"
#include <iostream>

HelpCommand::HelpCommand(ISchedule* _s)
{
	s = _s;
}

size_t HelpCommand::getNumberOfWords() const
{
	return numOfWords;
}

void HelpCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->help();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string HelpCommand::toString() const
{
	return "help";
}
