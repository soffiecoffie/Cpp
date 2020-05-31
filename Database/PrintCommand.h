#ifndef PRINTCOMMAND__H
#define PRINTCOMMAND__H

#include "ICommand.h"


class PrintCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	PrintCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif