#ifndef NEXTPAGECOMMAND__H
#define NEXTPAGECOMMAND__H

#include "ICommand.h"


class NextPageCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	NextPageCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif