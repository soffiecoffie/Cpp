#include "ExitCommand.h"
#include <iostream>

ExitCommand::ExitCommand(ISchedule* _s)
{
	s = _s;
}

size_t ExitCommand::getNumberOfWords() const
{
	return numOfWords;
}

void ExitCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->exit();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ExitCommand::toString() const
{
	return "exit";
}
