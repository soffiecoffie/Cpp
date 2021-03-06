﻿#include "ExitCommand.h"
#include <iostream>

/** @brief конструктор с параметър*/
ExitCommand::ExitCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ExitCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата exit */
void ExitCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->exit();
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string ExitCommand::toString() const
{
	return "exit";
}
