﻿#ifndef CHANGECOMMAND_H
#define CHANGECOMMAND_H

#include "ICommand.h"

/** @brief клас ChangeCommand помага за извикването на командата change от потребителя*/
class ChangeCommand : public ICommand
{
	size_t min = 5;
	size_t max = 625;

public:
	ChangeCommand(ISchedule*);
	/** @brief деструктор */
	~ChangeCommand() {};

	size_t getNumberOfWords() const;
	size_t getMinNumberOfWords() const;
	size_t getMaxNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif