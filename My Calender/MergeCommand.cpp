#include "MergeCommand.h"
#include "Utils.h"
#include <vector>
#include <iostream>

MergeCommand::MergeCommand(ISchedule* _s)
{
	s = _s;
}

size_t MergeCommand::getNumberOfWords() const
{
	return getMinNumberOfWords();
}

size_t MergeCommand::getMinNumberOfWords() const
{
	return min;
}

size_t MergeCommand::getMaxNumberOfWords() const
{
	return max;
}

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

std::string MergeCommand::toString() const
{
	return "merge";
}
