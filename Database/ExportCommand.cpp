#include "ExportCommand.h"

ExportCommand::ExportCommand(IDatabase* _db)
{
	db = _db;
}

size_t ExportCommand::getNumberOfWords() const
{
	return numOfWords;
}

void ExportCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->myExport(getWord(2, input), getWord(3, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ExportCommand::toString() const
{
	return "export";
}
