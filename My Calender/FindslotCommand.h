#ifndef FINDSLOTCOMMAND_H
#define FINDSLOTCOMMAND_H

#include "ICommand.h"

/** @brief клас FindslotCommand помага за извикването на командата findslot от потребителя*/
class FindslotCommand : public ICommand
{
	size_t numOfWords = 3;

public:
	FindslotCommand(ISchedule*);
	/** @brief деструктор */
	~FindslotCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif