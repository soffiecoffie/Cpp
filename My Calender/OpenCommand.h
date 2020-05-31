#ifndef OPENCOMMAND_H
#define OPENCOMMAND_H

#include "ICommand.h"

/** @brief клас OpenCommand помага за извикването на командата open от потребителя*/
class OpenCommand :	public ICommand
{
private:
	size_t numOfWords = 2;

public:
	OpenCommand(ISchedule*);
	/** @brief деструктор */
	~OpenCommand() {};
	
	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
