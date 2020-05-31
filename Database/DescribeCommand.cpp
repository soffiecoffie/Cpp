#include "DescribeCommand.h"

DescribeCommand::DescribeCommand(IDatabase* _db)
{
	db = _db;
}

size_t DescribeCommand::getNumberOfWords() const
{
	return numOfWords;
}

void DescribeCommand::execute(std::string input) const
{
	if (db->getIsOpen())
		db->describe(getWord(2, input));
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string DescribeCommand::toString() const
{
	return "describe";
}
