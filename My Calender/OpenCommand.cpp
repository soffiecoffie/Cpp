#include "OpenCommand.h"
#include <string>
#include <fstream>
#include <iostream>

/** @brief конструктор с параметър*/
OpenCommand::OpenCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t OpenCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата open */
void OpenCommand::execute(std::string input) const
{
	s->open(input);
}

/** @brief връща символен низ от името на командата */
std::string OpenCommand::toString() const
{
	return "open";
}
