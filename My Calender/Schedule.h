#ifndef SCHEDULE_H
#define SCEDULE_H
#include "Arrangement.h"

class Schedule {
	size_t size;
	Arrangement* arr;

	void addSize(size_t);
	bool hasStr(const char*, const char*) const; //checks if a given string can be found in another
		//TODO change hasStr so that i can arr.hasStr(str) 
public:
	Schedule() : arr(nullptr), size(0) {};
	Schedule(const Arrangement*, size_t); //const?

	int findIndex(const Date&, const Time&);				//find by start time and day!
	size_t getBusyMinutes(const Date&) const;//TODO
	bool overlap(const Arrangement&) const;					//checks if new arrangement overlaps others 
	bool overlapOthers(const Arrangement&, int ind) const;			//checks if existing arrangement overlaps others
	void swapArrangements(size_t, size_t);
	void sortChronologically();
	bool isHoliday(const Date&) const;
	bool hasFreeSlot(const Date&, size_t) const; //test this
	MeetingTime getFreeSlot(const Date& d, size_t hours) const;
	void print() const;

	void book(const Arrangement&);
	void unbook(const Date&, MeetingTime);
	void agenda(const Date& date);
	void change(const Date&, const Time&, const char*, const Date&);	//promenq denq
	void change(const Date&, const Time&, const char*, const Time&);	//start/endtime
	void change(const Date&, const Time&, const char*, const char*);	//note/name
	void find(const char*) const;
	void holiday(const Date&);
	void busydays(const Date&, const Date&) const;
	Date findslot(const Date&, size_t) const;
	Date findslotwith(const Date&, size_t, const Schedule*, size_t) const; //const schedule?
	Date findslotwithOneCal(const Date&, size_t, const Schedule&) const; 
	void merge(const Schedule*);
};


#endif 
