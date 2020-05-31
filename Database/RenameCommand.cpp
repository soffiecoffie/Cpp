#include "RenameCommand.h"
#include <iostream>

RenameCommand::RenameCommand(IDatabase* _db)
{
	db = _db;
}

size_t RenameCommand::getNumberOfWords() const
{
	return numOfWords;
}

void RenameCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->rename(getWord(2, input), getWord(3, input));
	else
		std::cout << "You can't use this command now!\n";
}

std::string RenameCommand::toString() const
{
	return "rename";
}
