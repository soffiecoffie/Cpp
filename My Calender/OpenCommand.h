#ifndef OPENCOMMAND_H
#define OPENCOMMAND_H

#include "ICommand.h"
#include "ISchedule.h"

class OpenCommand :	public ICommand
{
private:
	size_t numOfWords = 2;

public:
	OpenCommand(ISchedule*);
	
	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
