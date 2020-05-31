#include "DescribeCommand.h"

/** @brief конструктор с параметър*/
DescribeCommand::DescribeCommand(IDatabase* _db)
{
	db = _db;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t DescribeCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата describe */
void DescribeCommand::execute(std::string input) const
{
	if (db->getIsOpen() && !db->getIsPageCmdOn())
		db->describe(getWord(2, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string DescribeCommand::toString() const
{
	return "describe";
}
