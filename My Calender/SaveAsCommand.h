#ifndef SAVEASCOMMAND__H
#define SAVEASCOMMAND__H

#include "ICommand.h"

/** @brief клас SaveAsCommand помага за извикването на командата saveas от потребителя*/
class SaveAsCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	SaveAsCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};


#endif 