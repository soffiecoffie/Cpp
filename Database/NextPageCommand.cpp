#include "NextPageCommand.h"
#include <iostream>

NextPageCommand::NextPageCommand(IDatabase* _db)
{
	db = _db;
}

size_t NextPageCommand::getNumberOfWords() const
{
	return numOfWords;
}

void NextPageCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->next(getWord(2,input));
	else
		std::cout << "You can't use this command now!\n";
}

std::string NextPageCommand::toString() const
{
	return "next";
}
