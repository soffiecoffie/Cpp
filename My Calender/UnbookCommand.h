#ifndef UNBOOKCOMMAND__H
#define UNBOOKCOMMAND__H

#include "ICommand.h"

/** @brief клас UnbookCommand помага за извикването на командата unbook от потребителя*/
class UnbookCommand : public ICommand
{
	size_t numOfWords = 4;

public:
	UnbookCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif