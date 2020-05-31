#include "AddColumnCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
AddColumnCommand::AddColumnCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t AddColumnCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата addcolumn */
void AddColumnCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->addColumn(getWord(2, input), getWord(3, input), getWord(4, input));
	else
		std::cout << "You can't use this command now!\n";
}

/** @brief връща символен низ от името на командата */
std::string AddColumnCommand::toString() const
{
	return "addcolumn";
}
