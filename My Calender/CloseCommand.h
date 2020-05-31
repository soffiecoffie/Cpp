#ifndef CLOSECOMMAND_H
#define CLOSECOMMAND_H

#include "ICommand.h"

/** @brief клас CloseCommand помага за извикването на командата close от потребителя*/
class CloseCommand : public ICommand
{
	size_t numOfWords = 1;

public:
	CloseCommand(ISchedule* _s);
	/** @brief деструктор */
	~CloseCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif