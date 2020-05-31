#ifndef BUSYDAYSCOMMAND_H
#define BUSYDAYSCOMMAND_H

#include "ICommand.h"

/** @brief клас BusydaysCommand помага за извикването на командата busydays от потребителя */
class BusydaysCommand : public ICommand
{
	size_t numOfWords = 3;

public:
	BusydaysCommand(ISchedule*);
	/** @brief деструктор */
	~BusydaysCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif