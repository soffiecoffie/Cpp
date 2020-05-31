#include "FindslotwithCommand.h"
#include "Schedule.h"
#include "Utils.h"
#include <vector>
#include <iostream>

/** @brief конструктор с параметър*/
FindslotwithCommand::FindslotwithCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t FindslotwithCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

/** @brief връща минималният брой на думите, които са необходими за тази команда */
size_t FindslotwithCommand::getMinNumberOfWords() const
{
	return min;
}

/** @brief връща максималният брой на думите, които съставят тази команда */
size_t FindslotwithCommand::getMaxNumberOfWords() const
{
	return max;
}

/** @brief извиква командата findslotwith */
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

/** @brief връща символен низ от името на командата */
std::string FindslotwithCommand::toString() const
{
	return "findslotwith";
}
