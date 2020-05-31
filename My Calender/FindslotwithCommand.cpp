#include "FindslotwithCommand.h"
#include "Schedule.h"
#include "Utils.h"
#include <vector>
#include <iostream>

FindslotwithCommand::FindslotwithCommand(ISchedule* _s)
{
	s = _s;
}

size_t FindslotwithCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

size_t FindslotwithCommand::getMinNumberOfWords() const
{
	return min;
}

size_t FindslotwithCommand::getMaxNumberOfWords() const
{
	return max;
}

void FindslotwithCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		std::string from = getWord(2, input);
		std::string hours = getWord(3, input);
		Date fromDay = fromDay.stringToDate(from);
		
		std::vector<std::string> files;
		for (size_t i = 4; i <= getNumOfWords(input); ++i)
		{
			files.push_back(getWord(i, input));
		}

		std::cout << "There is a free slot on " << s->findslotwith(fromDay, stoul(hours), files, files.size()) << std::endl;
		std::cout << "This command was successful!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

std::string FindslotwithCommand::toString() const
{
	return "findslotwith";
}
