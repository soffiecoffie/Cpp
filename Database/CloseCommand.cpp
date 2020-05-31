#include "CloseCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
CloseCommand::CloseCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t CloseCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата close */
void CloseCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->close();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string CloseCommand::toString() const
{
	return "close";
}
