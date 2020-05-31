#ifndef RENAMECOMMAND_H
#define RENAMECOMMAND_H

#include "ICommand.h"

/** @brief клас RenameCommand помага за извикването на командата rename от потребителя*/
class RenameCommand : public ICommand
{
	size_t numOfWords = 3;

public:
	RenameCommand(IDatabase*);
	/** @brief деструктор */
	~RenameCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif