#ifndef SHOWTABLESCOMMAND_H
#define SHOWTABLESCOMMAND_H

#include "ICommand.h"

/** @brief клас ShowtablesCommand помага за извикването на командата showtables от потребителя*/
class ShowtablesCommand : public ICommand
{
private:
	size_t numOfWords = 1;

public:
	ShowtablesCommand(IDatabase*);
	/** @brief деструктор */
	~ShowtablesCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
