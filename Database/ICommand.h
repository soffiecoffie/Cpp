#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include "IDatabase.h"
#include "Utils.h"
#include <iostream>

class ICommand
{
protected:
	IDatabase* db = nullptr;

public:
	virtual void execute(std::string) const = 0;
	virtual std::string toString() const = 0;
	virtual size_t getNumberOfWords() const = 0;
	virtual size_t getMinNumberOfWords() const;
	virtual size_t getMaxNumberOfWords() const;

};

#endif