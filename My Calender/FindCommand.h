﻿#ifndef FINDCOMMAND__H
#define FINDCOMMAND__H

#include "ICommand.h"

/** @brief клас FindCommand помага за извикването на командата find от потребителя*/
class FindCommand : public ICommand
{
	size_t numOfWords = 2;

public:
	FindCommand(ISchedule*);

	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif