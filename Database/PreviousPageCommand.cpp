#include "PreviousPageCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
PreviousPageCommand::PreviousPageCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t PreviousPageCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата previous */
void PreviousPageCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->previous(getWord(2,input));
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string PreviousPageCommand::toString() const
{
	return "previous";
}
