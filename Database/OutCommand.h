#ifndef OUTCOMMAND__H
#define OUTCOMMAND__H

#include "ICommand.h"


class OutCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	OutCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif