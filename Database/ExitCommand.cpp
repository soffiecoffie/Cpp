#include "ExitCommand.h"
#include <iostream>

ExitCommand::ExitCommand(IDatabase* _db)
{
	db = _db;
}

size_t ExitCommand::getNumberOfWords() const
{
	return numOfWords;
}

void ExitCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->exit();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ExitCommand::toString() const
{
	return "exit";
}
