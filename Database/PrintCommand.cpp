#include "PrintCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
PrintCommand::PrintCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t PrintCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата print */
void PrintCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->print(getWord(2, input));
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string PrintCommand::toString() const
{
	return "print";
}
