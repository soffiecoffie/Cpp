#include "ShowtablesCommand.h"

ShowtablesCommand::ShowtablesCommand(IDatabase* _db)
{
	db = _db;
}

size_t ShowtablesCommand::getNumberOfWords() const
{
	return numOfWords;
}

void ShowtablesCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->showtables();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ShowtablesCommand::toString() const
{
	return "showtables";
}
