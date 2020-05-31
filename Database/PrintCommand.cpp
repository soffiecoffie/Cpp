#include "PrintCommand.h"
#include <iostream>

PrintCommand::PrintCommand(IDatabase* _db)
{
	db = _db;
}

size_t PrintCommand::getNumberOfWords() const
{
	return numOfWords;
}

void PrintCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->print(getWord(2, input));
	else
		std::cout << "You can't use this command now!\n";
}

std::string PrintCommand::toString() const
{
	return "print";
}
