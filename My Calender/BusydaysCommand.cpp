#include "BusydaysCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

/** @brief конструктор с параметър*/
BusydaysCommand::BusydaysCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t BusydaysCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата busydays */
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

/** @brief връща символен низ от името на командата */
std::string BusydaysCommand::toString() const
{
	return "busydays";
}
