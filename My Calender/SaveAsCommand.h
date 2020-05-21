#ifndef SAVEASCOMMAND_H
#define SAVEASCOMMAND_H

#include "ICommand.h"

class SaveAsCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	SaveAsCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 