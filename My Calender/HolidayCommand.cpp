#include "HolidayCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

HolidayCommand::HolidayCommand(ISchedule* _s)
{
	s = _s;
}

size_t HolidayCommand::getNumberOfWords() const
{
	return numOfWords;
}

void HolidayCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);

		Date day = day.stringToDate(date);

		s->holiday(day);
		std::cout << "Successfuly marked" << day << "as a holiday\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string HolidayCommand::toString() const
{
	return "holiday";
}
