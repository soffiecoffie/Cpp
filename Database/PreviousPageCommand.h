#ifndef PREVIOUSPAGECOMMAND_H
#define PREVIOUSPAGECOMMAND_H

#include "ICommand.h"

/** @brief клас PreviousPageCommand помага за извикването на командата previous от потребителя*/
class PreviousPageCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	PreviousPageCommand(IDatabase*);
	/** @brief деструктор */
	~PreviousPageCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif