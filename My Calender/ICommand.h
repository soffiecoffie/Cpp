#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include "ISchedule.h"

/** @brief клас ICommand е интерфейсен клас на всички команди*/
class ICommand
{
protected:
	ISchedule* s = nullptr;

public:
	virtual void execute(std::string) const = 0;
	virtual std::string toString() const = 0;
	virtual size_t getNumberOfWords() const = 0;
	virtual size_t getMinNumberOfWords() const;
	virtual size_t getMaxNumberOfWords() const;
	virtual std::string getWord(size_t, const std::string&) const;
	virtual std::string getStringAfterWord(size_t num, const std::string& str) const;

};

#endif