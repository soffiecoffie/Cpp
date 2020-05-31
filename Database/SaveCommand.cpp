#include "SaveCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
SaveCommand::SaveCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t SaveCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата save */
void SaveCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->save();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string SaveCommand::toString() const
{
	return "save";
}
