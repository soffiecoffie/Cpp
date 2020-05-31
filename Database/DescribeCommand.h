#ifndef DESCRIBECOMMAND_H
#define DESCRIBECOMMAND_H

#include "ICommand.h"

/** @brief клас DescribeCommand помага за извикването на командата describe от потребителя*/
class DescribeCommand :	public ICommand
{
private:
	size_t numOfWords = 2;

public:
	DescribeCommand(IDatabase*);
	/** @brief деструктор */
	~DescribeCommand() {};
	
	size_t getNumberOfWords() const;
	void execute(std::string) const;
	std::string toString() const;
};

#endif
