#include "PreviousPageCommand.h"
#include <iostream>

PreviousPageCommand::PreviousPageCommand(IDatabase* _db)
{
	db = _db;
}

size_t PreviousPageCommand::getNumberOfWords() const
{
	return numOfWords;
}

void PreviousPageCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn())
		db->previous(getWord(2,input));
	else
		std::cout << "You can't use this command now!\n";
}

std::string PreviousPageCommand::toString() const
{
	return "previous";
}
