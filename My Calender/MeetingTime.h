#ifndef MEETINGTIME_H
#define MEETINGTIME_H
#include "Time.h"
#include <string>
#include <cassert>

/** @brief структура, която събира началото и края на дадено събитие/среща в едно */
struct MeetingTime {
	Time start;			
	Time end;
	
	/** @brief конструктор по подразбиране */
	MeetingTime() : start(Time()), end(Time()) {};
	/** @brief конструктор с параметри */
	MeetingTime(Time start, Time end) : start(start), end(end) { assert(start < end); };
	/** @brief предефинира оператор == */
	bool operator==(const MeetingTime& other)const { return start == other.start && end == other.end; }
};



#endif