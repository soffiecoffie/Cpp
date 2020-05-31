#include "SaveCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
SaveCommand::SaveCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t SaveCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата save */
void SaveCommand::execute(std::string input) const
{
	if (s->getIsOpen())
		s->save();	
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string SaveCommand::toString() const
{
	return "save";
}
