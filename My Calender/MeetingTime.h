#ifndef MEETINGTIME_H
#define MEETINGTIME_H
#include "Time.h"


struct MeetingTime {
	Time start;			//should it stay as a structure?
	Time end;

	MeetingTime() : start(Time()), end(Time()) {};
	MeetingTime(Time start, Time end) : start(start), end(end) {};
};



#endif
