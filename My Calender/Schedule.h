#ifndef SCHEDULE_H
#define SCEDULE_H
#include "Arrangement.h"

class Schedule {
	size_t size;
	Arrangement* arr;

	void addSize(size_t);
	bool hasStr(const char*, const char*) const; //checks if a given string can be found in another

public:
	Schedule() : arr(nullptr), size(0) {};
	Schedule(Arrangement*, size_t);

	int findIndex(const Date&, const Time&);				//find by start time and day!
	int getBusyHours(const Date&) const;//TODO
	bool overlap(const Arrangement&) const;					//checks if new arrangement overlaps others 
	bool overlapOthers(const Arrangement&, int ind) const;			//checks if existing arrangement overlaps others
	void print() const;

	void book(const Arrangement&);
	void unbook(const Date&, MeetingTime);
	void agenda(const Date& date) const;
	void change(const Date&, const Time&, const char*, const Date&);	//promenq denq
	void change(const Date&, const Time&, const char*, const Time&);	//start/endtime
	void change(const Date&, const Time&, const char*, const char*);	//note/name
	void find(const char*) const;
	void holiday(const Date&);
	void busydays(const Date&, const Date&) const;
};


#endif 
