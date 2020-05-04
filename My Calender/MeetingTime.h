#ifndef MEETINGTIME_H
#define MEETINGTIME_H
#include "Time.h"

//структура, която събира началото и края на дадено събитие/среща в едно
struct MeetingTime {
	Time start;			//should it stay as a structure?
	Time end;

	MeetingTime() : start(Time()), end(Time()) {};
	MeetingTime(Time start, Time end) : start(start), end(end) {};
};



#endif
