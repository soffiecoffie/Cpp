#include "ChangeCommand.h"
#include "Arrangement.h"
#include <iostream>

/** @brief конструктор с параметър*/
ChangeCommand::ChangeCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t ChangeCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

/** @brief връща минималният брой на думите, които са необходими за тази команда */
size_t ChangeCommand::getMinNumberOfWords() const
{
	return min;
}

/** @brief връща максималният брой на думите, които съставят тази команда */
size_t ChangeCommand::getMaxNumberOfWords() const
{
	return max;
}

/** @brief извиква командата change */
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

/** @brief връща символен низ от името на командата */
std::string ChangeCommand::toString() const
{
	return "change";
}
