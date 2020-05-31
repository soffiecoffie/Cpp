#ifndef OPENCOMMAND__H
#define OPENCOMMAND__H

#include "ICommand.h"
#include "ISchedule.h"

/** @brief клас OpenCommand помага за извикването на командата open от потребителя*/
class OpenCommand :	public ICommand
{
private:
	size_t numOfWords = 2;

public:
	OpenCommand(ISchedule*);
	
	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
