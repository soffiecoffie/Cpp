#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "ICommand.h"

class SaveCommand :	public ICommand
{
	size_t numOfWords = 1;

public:
	SaveCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;

};


#endif