#include "HelpCommand.h"
#include <iostream>

HelpCommand::HelpCommand(IDatabase* _db)
{
	db = _db;
}

size_t HelpCommand::getNumberOfWords() const
{
	return numOfWords;
}

void HelpCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->help();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string HelpCommand::toString() const
{
	return "help";
}
