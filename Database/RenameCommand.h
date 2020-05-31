#ifndef RENAMECOMMAND__H
#define RENAMECOMMAND__H

#include "ICommand.h"


class RenameCommand : public ICommand
{
	size_t numOfWords = 3;

public:
	RenameCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif