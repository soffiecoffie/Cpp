#include "ExportCommand.h"

/** @brief конструктор с параметър*/
ExportCommand::ExportCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ExportCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата export */
void ExportCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->myExport(getWord(2, input), getWord(3, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string ExportCommand::toString() const
{
	return "export";
}
