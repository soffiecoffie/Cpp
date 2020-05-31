#include "SaveAsCommand.h"
#include <iostream>

SaveAsCommand::SaveAsCommand(IDatabase* _db)
{
	db = _db;
}

size_t SaveAsCommand::getNumberOfWords() const
{
	return numOfWords;
}

void SaveAsCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->saveas(getWord(2,input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string SaveAsCommand::toString() const
{
	return "saveas";
}
