#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "ICommand.h"


/** @brief клас HelpCommand помага за извикването на командата help от потребителя*/
class HelpCommand : public ICommand
{
private:
	size_t numOfWords = 1;

public:
	HelpCommand(IDatabase*);
	/** @brief деструктор */
	~HelpCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 