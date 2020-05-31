#ifndef EXPORTCOMMAND_H
#define EXPORTCOMMAND_H

#include "ICommand.h"

/** @brief клас ExportCommand помага за извикването на командата export от потребителя*/
class ExportCommand : public ICommand
{
private:
	size_t numOfWords = 3;

public:
	ExportCommand(IDatabase*);
	/** @brief деструктор */
	~ExportCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
