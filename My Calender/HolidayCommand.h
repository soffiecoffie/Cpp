#ifndef HOLIDAYCOMMAND_H
#define HOLIDAYCOMMAND_H

#include "ICommand.h"

/** @brief клас HolidayCommand помага за извикването на командата holiday от потребителя*/
class HolidayCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	HolidayCommand(ISchedule*);
	/** @brief деструктор */
	~HolidayCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif