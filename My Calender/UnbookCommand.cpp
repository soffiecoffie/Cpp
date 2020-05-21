#include "UnbookCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

UnbookCommand::UnbookCommand(ISchedule* _s)
{
	s = _s;
}

size_t UnbookCommand::getNumberOfWords() const
{
	return numOfWords;
}

void UnbookCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);
		std::string starttime = getWord(3, input);
		std::string endtime = getWord(4, input);//getStringAfterWord(3, input);//getWord(4, input);

		Date day = day.stringToDate(date);
		Time start, end;
		start = start.stringToTime(starttime);
		end = end.stringToTime(endtime);

		s->unbook(day, MeetingTime(start, end));
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string UnbookCommand::toString() const
{
	return "unbook";
}
