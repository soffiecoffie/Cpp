#include "NextPageCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
NextPageCommand::NextPageCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t NextPageCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата next */
void NextPageCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->next(getWord(2,input));
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string NextPageCommand::toString() const
{
	return "next";
}
