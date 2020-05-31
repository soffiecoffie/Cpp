#ifndef ADDCOLUMNCOMMAND__H
#define ADDCOLUMNCOMMAND__H

#include "ICommand.h"


class AddColumnCommand : public ICommand
{
	size_t numOfWords = 4;

public:
	AddColumnCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif