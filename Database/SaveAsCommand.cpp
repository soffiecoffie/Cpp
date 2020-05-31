#include "SaveAsCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
SaveAsCommand::SaveAsCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t SaveAsCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата saveas */
void SaveAsCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->saveas(getWord(2,input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string SaveAsCommand::toString() const
{
	return "saveas";
}
