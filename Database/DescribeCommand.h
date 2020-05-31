#ifndef DESCRIBECOMMAND__H
#define DESCRIBECOMMAND__H

#include "ICommand.h"

class DescribeCommand :	public ICommand
{
private:
	size_t numOfWords = 2;

public:
	DescribeCommand(IDatabase*);
	
	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
