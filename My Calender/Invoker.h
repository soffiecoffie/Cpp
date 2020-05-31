#ifndef INVOKER__H
#define INVOKER__H

#include "ICommand.h"
#include <vector>
#include <string>

/** @brief клас Invoker помага за извикването на дадена команда от потребителя*/
class Invoker
{
	std::vector<ICommand*> commands;

public:
	Invoker(ISchedule*);

	void executeCmd(std::string);
};


#endif