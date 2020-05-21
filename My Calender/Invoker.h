#ifndef INVOKER__H
#define INVOKER__H

#include "ICommand.h"
#include <vector>
#include <string>

class Invoker
{
	std::vector<ICommand*> commands;

public:
	Invoker(ISchedule*);

	void executeCmd(std::string);
};


#endif