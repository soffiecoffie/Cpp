#include "HolidayCommand.h"
#include "MeetingTime.h"
#include "Date.h"
#include <iostream>

/** @brief конструктор с параметър*/
HolidayCommand::HolidayCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t HolidayCommand::getNumberOfWords() const
{
	return numOfWords;
}

/** @brief извиква командата help */
void HolidayCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string date = getWord(2, input);

		Date day = day.stringToDate(date);

		s->holiday(day);
		std::cout << "Successfuly marked " << day << " as a holiday\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string HolidayCommand::toString() const
{
	return "holiday";
}
