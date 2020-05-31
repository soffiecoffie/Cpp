#include <iostream>
#include "Schedule.h"
#include "Invoker.h"

int main()
{
	std::cout << "Welcome to your personal calendar!\n";
	std::cout << "To open or create a new calendar write open <filename>:\n\n";
	Schedule s;
	
	ISchedule* sptr = &s;
	Invoker n(sptr);
	
	std::string input;
	while (!sptr->getIsDone())
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		n.executeCmd(input);
	}
	std::cout << std::endl;
	
	return 0;
}