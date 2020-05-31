#include "OutCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
OutCommand::OutCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t OutCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата out */
void OutCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->out();
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string OutCommand::toString() const
{
	return "out";
}
