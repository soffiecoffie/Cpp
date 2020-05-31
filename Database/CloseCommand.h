#ifndef CLOSECOMMAND_H
#define CLOSECOMMAND_H

#include "ICommand.h"

class CloseCommand : public ICommand
{
	size_t numOfWords = 1;

public:
	CloseCommand(IDatabase* _s);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif