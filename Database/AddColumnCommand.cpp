#include "AddColumnCommand.h"
#include <iostream>

AddColumnCommand::AddColumnCommand(IDatabase* _db)
{
	db = _db;
}

size_t AddColumnCommand::getNumberOfWords() const
{
	return numOfWords;
}

void AddColumnCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->addColumn(getWord(2, input), getWord(3, input), getWord(4, input));
	else
		std::cout << "You can't use this command now!\n";
}

std::string AddColumnCommand::toString() const
{
	return "addcolumn";
}
