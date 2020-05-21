#include "BookCommand.h"
#include "Arrangement.h"
#include <iostream>

BookCommand::BookCommand(ISchedule* _s)
{
	s = _s;
}

size_t BookCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

size_t BookCommand::getMinNumberOfWords() const
{
	return min;
}

size_t BookCommand::getMaxNumberOfWords() const
{
	return max;
}

void BookCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);
		std::string starttime = getWord(3, input);
		std::string endtime = getWord(4, input);
		std::string name = getWord(5, input);
		std::string note = getStringAfterWord(5, input);

		Date day = day.stringToDate(date);
		Time start, end;
		start = start.stringToTime(starttime);
		end = end.stringToTime(endtime);

		Arrangement arr(name.c_str(), note.c_str(), day, MeetingTime(start, end));
		s->book(arr);

		std::cout << "Successfully booked an appointment!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string BookCommand::toString() const
{
	return "book";
}
