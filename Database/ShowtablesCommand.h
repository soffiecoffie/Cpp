#ifndef SHOWTABLESCOMMAND__H
#define SHOWTABLESCOMMAND__H

#include "ICommand.h"

class ShowtablesCommand : public ICommand
{
private:
	size_t numOfWords = 1;

public:
	ShowtablesCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
