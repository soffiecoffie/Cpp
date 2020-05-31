#include "ISchedule.h"
#include <iostream>

/** @brief виртуална функция, която изписва на екрана всички поддържани команди с кратко обяснение*/
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
		<< "  with <name> about <note> from <starttime> to <endtime> on <date>\n"
		<< "> unbook <date> <starttime> <endtime> - unbooks an appointment on <date>\n"
		<< "  from <starttime> to <endtime> \n"
		<< "> agenda <date> - prints all arrangements on <date> chronologically\n"
		<< "> change <date> <starttime> <option> <newvalue> - changes the <option> \n"
		<< "  (date/starttime/endtime/note/name) of an arrangement on <date> at <starttime>\n"
		<< "  with a <newvalue> \n"
		<< "> find <string> - prints all arrangements that contain <string> \n"
		<< "> holiday <date> - marks <date> as a holiday\n"
		<< "> busydays <from> <to> - prints all days <from> <to> sorted by busyness\n"
		<< "> findslot <fromdate> <hours> - finds a free slot for an arrangement from \n"
		<< "  <fromdate> between 08:00 and 17:00 for <hours>\n"
		<< "> findslotwith <fromdate> <hours> <calendar/s> - finds a free slot synced with all\n"
		<< "  calendars for an arrangement on <fromdate> between 08:00 and 17:00 for <hours>\n"
		<< "> merge <calendar/s> - merges all calendars in the current calendar\n\n";
}
