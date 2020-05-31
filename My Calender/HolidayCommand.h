#ifndef HOLIDAYCOMMAND__H
#define HOLIDAYCOMMAND__H

#include "ICommand.h"

/** @brief клас HolidayCommand помага за извикването на командата holiday от потребителя*/
class HolidayCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	HolidayCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif