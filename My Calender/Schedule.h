#ifndef SCHEDULE_H
#define SCEDULE_H
#include "Arrangement.h"

class Schedule {
	size_t size;
	Arrangement* arr;

	void addSize(size_t);

public:
	Schedule() : arr(nullptr), size(0) {};
	Schedule(Arrangement*, size_t);

	void book(const Arrangement&);
	void unbook(const Date&, MeetingTime);


	bool overlap(const Arrangement&) const;
	void print() const;
	void agenda(const Date& date) const;
};


#endif 
