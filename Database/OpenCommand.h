#ifndef OPENCOMMAND__H
#define OPENCOMMAND__H

#include "ICommand.h"

class OpenCommand : public ICommand
{
private:
	size_t numOfWords = 2;

public:
	OpenCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
