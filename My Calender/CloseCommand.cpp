#include "CloseCommand.h"
#include <iostream>

CloseCommand::CloseCommand(ISchedule* _s)
{
	s = _s;
}

size_t CloseCommand::getNumberOfWords() const
{
	return numOfWords;
}

void CloseCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->close();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string CloseCommand::toString() const
{
	return "close";
}
