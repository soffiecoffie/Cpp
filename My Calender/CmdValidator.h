#ifndef CMDVALIDATOR__H
#define CMDVALIDATOR__H

#include "ICommand.h"

class CmdValidator
{
public:
	static size_t numOfWords(std::string);
	static std::string getFistWord(std::string);
	static size_t getFirstSpaceInd(std::string);
	static bool validateCommand(const ICommand*, std::string);
};

#endif