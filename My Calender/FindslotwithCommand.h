#ifndef FINDSLOTWITHCOMMAND__H
#define FINDSLOTWITHCOMMAND__H

#include "ICommand.h"

/** @brief клас FindslotwithCommand помага за извикването на командата findslotwith от потребителя*/
class FindslotwithCommand : public ICommand
{
	size_t min = 4;
	size_t max = 24;

public:
	FindslotwithCommand(ISchedule*);

	size_t getNumberOfWords() const;
	size_t getMinNumberOfWords() const;
	size_t getMaxNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif