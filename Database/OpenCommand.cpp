#include "OpenCommand.h"
#include <fstream>
#include <iostream>

/** @brief конструктор с параметър*/
OpenCommand::OpenCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t OpenCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата open */
void OpenCommand::execute(std::string input) const
{
	if (db->getIsOpen() && db->getIsPageCmdOn()) {
		std::cout << "You can't use this command now!\n";
		return;
	}
	db->open(getWord(2,input));
}
/** @brief връща символен низ от името на командата */
std::string OpenCommand::toString() const
{
	return "open";
}
