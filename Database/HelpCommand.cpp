#include "HelpCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
HelpCommand::HelpCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t HelpCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата help */
void HelpCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->help();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string HelpCommand::toString() const
{
	return "help";
}
