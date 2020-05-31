#include "ImportCommand.h"

/** @brief конструктор с параметър*/
ImportCommand::ImportCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ImportCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата import */
void ImportCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->import(getWord(2, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string ImportCommand::toString() const
{
	return "import";
}
