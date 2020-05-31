#include "SaveAsCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
SaveAsCommand::SaveAsCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t SaveAsCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата saveas */
void SaveAsCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->saveas(input);	
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string SaveAsCommand::toString() const
{
	return "saveas";
}
