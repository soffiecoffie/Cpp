#ifndef CMDVALIDATOR__H
#define CMDVALIDATOR__H

#include "ICommand.h"

/** @brief клас CmdValidator проверява дали дадена команда е валидна*/
class CmdValidator
{
public:
	static bool validateCommand(const ICommand*, std::string);
};

#endif