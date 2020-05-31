#ifndef AGENDACOMMAND_H
#define AGENDACOMMAND_H

#include "ICommand.h"

/** @brief клас AgendaCommand помага за извикването на командата agenda от потребителя */
class AgendaCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	AgendaCommand(ISchedule*);
	/** @brief деструктор */
	~AgendaCommand(){};

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif