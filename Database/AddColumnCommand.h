#ifndef ADDCOLUMNCOMMAND_H
#define ADDCOLUMNCOMMAND_H

#include "ICommand.h"


/** @brief клас AddColumnCommand помага за извикването на командата addcolumn от потребителя*/
class AddColumnCommand : public ICommand
{
	size_t numOfWords = 4;

public:
	AddColumnCommand(IDatabase*);
	/** @brief деструктор */
	~AddColumnCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif