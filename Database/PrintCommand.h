#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "ICommand.h"

/** @brief клас PrintCommand помага за извикването на командата print от потребителя*/
class PrintCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	PrintCommand(IDatabase*);
	/** @brief деструктор */
	~PrintCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif