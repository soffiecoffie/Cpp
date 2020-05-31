#ifndef MERGECOMMAND__H
#define MERGECOMMAND__H

#include "ICommand.h"

/** @brief клас MergeCommand помага за извикването на командата merge от потребителя*/
class MergeCommand : public ICommand
{
	size_t min = 2;
	size_t max = 24;

public:
	MergeCommand(ISchedule*);

	size_t getNumberOfWords() const;
	size_t getMinNumberOfWords() const;
	size_t getMaxNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif