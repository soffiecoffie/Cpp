#include "BusydaysCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

BusydaysCommand::BusydaysCommand(ISchedule* _s)
{
	s = _s;
}

size_t BusydaysCommand::getNumberOfWords() const
{
	return numOfWords;
}

void BusydaysCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string from = getWord(2, input);
		std::string to = getWord(3, input);

		Date fromDay = fromDay.stringToDate(from);
		Date toDay = toDay.stringToDate(to);

		s->busydays(fromDay, toDay);
		std::cout << "This command was successful!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string BusydaysCommand::toString() const
{
	return "busydays";
}
