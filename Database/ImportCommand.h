#ifndef IMPORTCOMMAND_H
#define IMPORTCOMMAND_H

#include "ICommand.h"

/** @brief клас ImportCommand помага за извикването на командата import от потребителя*/
class ImportCommand : public ICommand
{
private:
	size_t numOfWords = 2;

public:
	ImportCommand(IDatabase*);
	/** @brief деструктор */
	~ImportCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
