#ifndef EXPORTCOMMAND__H
#define EXPORTCOMMAND__H

#include "ICommand.h"

class ExportCommand : public ICommand
{
private:
	size_t numOfWords = 3;

public:
	ExportCommand(IDatabase*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
