#ifndef SAVEASCOMMAND__H
#define SAVEASCOMMAND__H

#include "ICommand.h"

class SaveAsCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	SaveAsCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 