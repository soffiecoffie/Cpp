#include "OutCommand.h"
#include <iostream>

OutCommand::OutCommand(IDatabase* _db)
{
	db = _db;
}

size_t OutCommand::getNumberOfWords() const
{
	return numOfWords;
}

void OutCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->out();
	else
		std::cout << "You can't use this command now!\n";
}

std::string OutCommand::toString() const
{
	return "out";
}
