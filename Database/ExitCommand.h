#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "ICommand.h"

/** @brief клас ExitCommand помага за извикването на командата exit от потребителя*/
class ExitCommand : public ICommand
{
	size_t numOfWords = 1;

public:
	ExitCommand(IDatabase*);
	/** @brief деструктор */
	~ExitCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif