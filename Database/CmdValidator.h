#ifndef CMDVALIDATOR__H
#define CMDVALIDATOR__H

#include "ICommand.h"

class CmdValidator
{
public:
	static bool validateCommand(const ICommand*, std::string);
};

#endif