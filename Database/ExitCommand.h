#ifndef EXITCOMMAND__H
#define EXITCOMMAND__H

#include "ICommand.h"


class ExitCommand : public ICommand
{
	size_t numOfWords = 1;

public:
	ExitCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif