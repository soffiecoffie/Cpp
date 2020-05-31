#ifndef SAVEASCOMMAND_H
#define SAVEASCOMMAND_H

#include "ICommand.h"

/** @brief клас SaveAsCommand помага за извикването на командата saveas от потребителя*/
class SaveAsCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	SaveAsCommand(IDatabase*);
	/** @brief деструктор */
	~SaveAsCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 