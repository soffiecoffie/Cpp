#include "AgendaCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

/** @brief конструктор с параметър*/
AgendaCommand::AgendaCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t AgendaCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата agenda */
void AgendaCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);

		Date day = day.stringToDate(date);

		s->agenda(day);
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string AgendaCommand::toString() const
{
	return "agenda";
}
