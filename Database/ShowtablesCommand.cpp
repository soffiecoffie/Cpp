#include "ShowtablesCommand.h"

/** @brief конструктор с параметър*/
ShowtablesCommand::ShowtablesCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ShowtablesCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата showtables */
void ShowtablesCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->showtables();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string ShowtablesCommand::toString() const
{
	return "showtables";
}
