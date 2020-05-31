#ifndef PREVIOUSPAGECOMMAND__H
#define PREVIOUSPAGECOMMAND__H

#include "ICommand.h"


class PreviousPageCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	PreviousPageCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif