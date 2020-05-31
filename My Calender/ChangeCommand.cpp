#include "ChangeCommand.h"
#include "Arrangement.h"
#include <iostream>

ChangeCommand::ChangeCommand(ISchedule* _s)
{
	s = _s;
}

size_t ChangeCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

size_t ChangeCommand::getMinNumberOfWords() const
{
	return min;
}

size_t ChangeCommand::getMaxNumberOfWords() const
{
	return max;
}

void ChangeCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);
		std::string starttime = getWord(3, input);
		std::string option = getWord(4, input);
		std::string newvalue = getStringAfterWord(4, input);

		Date day = day.stringToDate(date);
		Time start;
		start = start.stringToTime(starttime);

		s->change(day, start, option, newvalue);
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string ChangeCommand::toString() const
{
	return "change";
}
