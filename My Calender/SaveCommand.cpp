#include "SaveCommand.h"
#include <iostream>

SaveCommand::SaveCommand(ISchedule* _s)
{
	s = _s;
}

size_t SaveCommand::getNumberOfWords() const
{
	return numOfWords;
}

void SaveCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->save();	
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string SaveCommand::toString() const
{
	return "save";
}
