#include "OpenCommand.h"
#include <string>
#include <fstream>
#include <iostream>

OpenCommand::OpenCommand(ISchedule* _s)
{
	s = _s;
}

size_t OpenCommand::getNumberOfWords() const
{
	return numOfWords;
}

void OpenCommand::execute(std::string input) const
{
	s->open(input);
}

std::string OpenCommand::toString() const
{
	return "open";
}
