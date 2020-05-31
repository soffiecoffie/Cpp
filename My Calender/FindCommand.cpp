#include "FindCommand.h"
#include <iostream>

FindCommand::FindCommand(ISchedule* _s)
{
	s = _s;
}

size_t FindCommand::getNumberOfWords() const
{
	return numOfWords;
}

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

std::string FindCommand::toString() const
{
	return "find";
}
