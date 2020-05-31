#include "CloseCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
CloseCommand::CloseCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t CloseCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата close */
void CloseCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->close();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string CloseCommand::toString() const
{
	return "close";
}
