#include "SaveAsCommand.h"
#include <iostream>

SaveAsCommand::SaveAsCommand(ISchedule* _s)
{
	s = _s;
}

size_t SaveAsCommand::getNumberOfWords() const
{
	return numOfWords;
}

void SaveAsCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->saveas(input);	
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string SaveAsCommand::toString() const
{
	return "saveas";
}
