#ifndef IMPORTCOMMAND_H
#define IMPORTCOMMAND_H

#include "ICommand.h"

class ImportCommand : public ICommand
{
private:
	size_t numOfWords = 2;

public:
	ImportCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
