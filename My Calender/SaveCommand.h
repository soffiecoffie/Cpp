#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include "ICommand.h"

/** @brief клас SaveCommand помага за извикването на командата save от потребителя*/
class SaveCommand :	public ICommand
{
	size_t numOfWords = 1;

public:
	SaveCommand(ISchedule*);
	/** @brief деструктор */
	~SaveCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;

};


#endif