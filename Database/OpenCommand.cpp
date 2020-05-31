#include "OpenCommand.h"
#include <fstream>
#include <iostream>

OpenCommand::OpenCommand(IDatabase* _db)
{
	db = _db;
}

size_t OpenCommand::getNumberOfWords() const
{
	return numOfWords;
}

void OpenCommand::execute(std::string input) const
{
	db->open(getWord(2,input));
}

std::string OpenCommand::toString() const
{
	return "open";
}
