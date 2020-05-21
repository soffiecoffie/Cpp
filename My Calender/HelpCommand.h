#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "ICommand.h"


class HelpCommand : public ICommand
{
private:
	size_t numOfWords = 1;

public:
	HelpCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 