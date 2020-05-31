#include "CloseCommand.h"
#include <iostream>

CloseCommand::CloseCommand(IDatabase* _db)
{
	db = _db;
}

size_t CloseCommand::getNumberOfWords() const
{
	return numOfWords;
}

void CloseCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->close();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string CloseCommand::toString() const
{
	return "close";
}
