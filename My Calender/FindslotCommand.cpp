#include "FindslotCommand.h"
#include "Date.h"
#include <iostream>

FindslotCommand::FindslotCommand(ISchedule* _s)
{
	s = _s;
}

size_t FindslotCommand::getNumberOfWords() const
{
	return numOfWords;
}

void FindslotCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string from = getWord(2, input);
		std::string hours = getWord(3, input);

		Date fromDay = fromDay.stringToDate(from);

		std::cout << "There is a free slot on " << s->findslot(fromDay, stoul(hours)) << std::endl;
		std::cout << "This command was successful!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string FindslotCommand::toString() const
{
	return "findslot";
}
