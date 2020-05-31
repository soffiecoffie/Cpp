#ifndef SAVECOMMAND__H
#define SAVECOMMAND__H

#include "ICommand.h"

class SaveCommand : public ICommand
{
	size_t numOfWords = 1;

public:
	SaveCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;

};


#endif