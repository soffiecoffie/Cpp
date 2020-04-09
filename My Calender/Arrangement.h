#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H
#include "Date.h"
#include "MeetingTime.h"

class Arrangement{
	char* name;
	char* note; 
	Date day;
	MeetingTime time; 

public:
	Arrangement() : name(nullptr), note(nullptr) {}; //shte se izvikat defaultnite na date i meetingtime right?
	Arrangement(const char*, const char*, Date, MeetingTime);
	~Arrangement();

	Date getDay() const { return day; };
	MeetingTime getTime() const{ return time; };
	char* getName() const { return name; };
	char* getNote() const { return note; };

	void setName(const char*);
	void setNote(const char*);
	void print() const;


	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Arrangement&);
	friend std::ostream& operator<<(std::ostream&, const Arrangement&);
};


#endif
