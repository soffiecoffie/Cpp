#include "UnbookCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

/** @brief конструктор с параметър*/
UnbookCommand::UnbookCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t UnbookCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата unbook */
void UnbookCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);
		std::string starttime = getWord(3, input);
		std::string endtime = getWord(4, input);

		Date day = day.stringToDate(date);
		Time start, end;
		start = start.stringToTime(starttime);
		end = end.stringToTime(endtime);

		if(s->unbook(day, MeetingTime(start, end)))
			std::cout << "Successfully unbooked an appointment!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string UnbookCommand::toString() const
{
	return "unbook";
}
