#ifndef BOOKCOMMAND__H
#define BOOKCOMMAND__H

#include "ICommand.h"

/** @brief клас BookCommand помага за извикването на командата book от потребителя*/
class BookCommand :	public ICommand
{
	size_t min = 6;
	size_t max = 625;

public:
	BookCommand(ISchedule*);

	size_t getNumberOfWords() const;
	size_t getMinNumberOfWords() const;
	size_t getMaxNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif