#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"
#include "Time.h"
#include "Schedule.h"
#include "OpenCommand.h"
#include "Invoker.h"

//check if you have unsuccessfull cases say they are succ after saying
int main()
{
	std::cout << "Welcome to your personal calendar!\n";
	std::cout << "To open or create a new calendar write \"open <filename>\":\n";
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
	//TODO for any new commands - add it in the help, push it in the invoker, say successful or not, add it in ISchedule
	//when can i use exit
	//s.print();
	return 0;
}