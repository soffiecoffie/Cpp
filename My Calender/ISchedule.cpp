#include "ISchedule.h"
#include <iostream>

void ISchedule::help()
{
	std::cout << "\nThe following commands are supported: \n\n"
		<< "> open <file> - opens <file>\n"
		<< "> close - closes currently opened file\n"
		<< "> save - saves the currently open file\n"
		<< "> saveas <file> - saves the currently opened file in <file>\n"
		<< "> help - prints this information\n"
		<< "> exit - exits the program\n"
		<< "> book <date> <starttime> <endtime> <name> <note> - books an appointment \n"
		<< "with <name> about <note> from <starttime> to <endtime> on <date>\n"
		<< "> unbook <date> <starttime> <endtime> - unbooks an appointment on <date>\n"
		<< "from <starttime> to <endtime> \n\n";
}
