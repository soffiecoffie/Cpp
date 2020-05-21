#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "ICommand.h"


class ExitCommand :	public ICommand
{
	size_t numOfWords = 1;

public:
	ExitCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif