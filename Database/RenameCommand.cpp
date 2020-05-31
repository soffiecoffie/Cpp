#include "RenameCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
RenameCommand::RenameCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t RenameCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата rename */
void RenameCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->rename(getWord(2, input), getWord(3, input));
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string RenameCommand::toString() const
{
	return "rename";
}
