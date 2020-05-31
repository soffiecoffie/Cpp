#ifndef OUTCOMMAND_H
#define OUTCOMMAND_H

#include "ICommand.h"

/** @brief клас OutCommand помага за извикването на командата out от потребителя*/
class OutCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	OutCommand(IDatabase*);
	/** @brief деструктор */
	~OutCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif