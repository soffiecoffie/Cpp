#include "MergeCommand.h"
#include "Utils.h"
#include <vector>
#include <iostream>

/** @brief конструктор с параметър*/
MergeCommand::MergeCommand(ISchedule* _s)
{
	s = _s;
}

/** @brief връща броя на думите, които са необходими за тази команда */
size_t MergeCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

/** @brief връща минималният брой на думите, които са необходими за тази команда */
size_t MergeCommand::getMinNumberOfWords() const
{
	return min;
}

/** @brief връща максималният брой на думите, които съставят тази команда */
size_t MergeCommand::getMaxNumberOfWords() const
{
	return max;
}

/** @brief извиква командата merge */
void MergeCommand::execute(std::string input) const
{
	if (s->getIsOpen()) {
		
		std::vector<std::string> files;

		for (size_t i = 2; i <= getNumOfWords(input); ++i)
		{
			files.push_back(getWord(i, input));
		}

		s->merge(files, files.size());
		std::cout << "This command was successful!\n";
	}
	else
		std::cout << "You can't use this command until you open a file!\n";
}

/** @brief връща символен низ от името на командата */
std::string MergeCommand::toString() const
{
	return "merge";
}
