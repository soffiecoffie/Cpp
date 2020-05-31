#ifndef INVOKER_H
#define INVOKER_H

#include "ICommand.h"
#include <vector>

/** @brief клас Invoker помага за извикването на дадена команда от потребителя*/
class Invoker
{
	std::vector<ICommand*> commands;

public:
	Invoker(IDatabase*);
	~Invoker();

	void executeCmd(std::string);
};


#endif