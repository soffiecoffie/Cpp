#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H
#include "Date.h"
#include "MeetingTime.h"

/** @brief клас Arrangement създава срещи*/
class Arrangement {
	bool holiday = false;
	char* name = nullptr; 
	char* note = nullptr; 
	Date day;
	MeetingTime time;

public:
	Arrangement() : name(nullptr), note(nullptr) {};
	Arrangement(const char*, const char*, const Date&, const MeetingTime&);
	Arrangement(const Date&, const MeetingTime&);
	Arrangement(bool, const Date&);
	Arrangement(const Arrangement&) = delete;
	~Arrangement();

	Date getDay() const { return day; };
	MeetingTime getTime() const { return time; };
	char* getName() const { return name; };
	char* getNote() const { return note; };
	bool getHoliday() const { return holiday; };
	size_t getLength() const;

	void setName(const char*);
	void setNote(const char*);
	void setHoliday(bool);
	void setDate(const Date&);
	void setStartTime(const Time&);
	void setEndTime(const Time&);
	void print() const;

	Arrangement& operator=(const Arrangement&); 

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;
	std::istream& readFromBin(std::istream&);
	std::ostream& writeToBin(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Arrangement&);
	friend std::ostream& operator<<(std::ostream&, const Arrangement&);
};


#endif