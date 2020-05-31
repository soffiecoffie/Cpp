#include "ImportCommand.h"

ImportCommand::ImportCommand(IDatabase* _db)
{
	db = _db;
}

size_t ImportCommand::getNumberOfWords() const
{
	return numOfWords;
}

void ImportCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->import(getWord(2, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ImportCommand::toString() const
{
	return "import";
}
