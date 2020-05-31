#include "SaveCommand.h"
#include <iostream>

SaveCommand::SaveCommand(IDatabase* _db)
{
	db = _db;
}

size_t SaveCommand::getNumberOfWords() const
{
	return numOfWords;
}

void SaveCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->save();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string SaveCommand::toString() const
{
	return "save";
}
