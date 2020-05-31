#ifndef NEXTPAGECOMMAND_H
#define NEXTPAGECOMMAND_H

#include "ICommand.h"


/** @brief клас NextPageCommand помага за извикването на командата next от потребителя*/
class NextPageCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	NextPageCommand(IDatabase*);
	/** @brief деструктор */
	~NextPageCommand() {};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif