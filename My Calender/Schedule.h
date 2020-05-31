#ifndef SCHEDULE__H
#define SCHEDULE__H

#include "ISchedule.h"
#include <string>
#include <vector>

/** @brief клас Schedule създава разписания със задължения за дните */
class Schedule : public ISchedule {
	size_t size;
	Arrangement* arr;
	std::string userFile = "";

	void addSize(size_t);
	bool hasStr(const char*, const char*) const; //checks if a given string can be found in another
												
	bool isDone = 0;
	bool isOpen = 0;
	void del();

public:
	Schedule() : arr(nullptr), size(0) {};
	Schedule(const Arrangement*, size_t); //const?
	~Schedule();

	void setUserFile(std::string);

	size_t getSize() const;
	Arrangement& getArrangement(size_t) const;
	int findIndex(const Date&, const Time&);				//find by start time and day!
	size_t getBusyMinutes(const Date&) const;//TODO
	bool overlap(const Arrangement&) const;					//checks if new arrangement overlaps others 
	bool overlapOthers(const Arrangement&, int ind) const;			//checks if existing arrangement overlaps others
	Arrangement& getOverlappedArr(const Arrangement&) const;
	void swapArrangements(size_t, size_t);
	void sortChronologically();
	bool isHoliday(const Date&) const;
	bool hasFreeSlot(const Date&, size_t) const; //test this
	MeetingTime getFreeSlot(const Date& d, size_t hours) const;
	Schedule allBusyHours(const Schedule*, size_t) const;
	Schedule& operator=(const Schedule&);
	void print() const;

	//връща масив от разписания от низ с имена на файлове
	Schedule* getCalendars(std::vector<std::string>) const;

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;
	std::istream& readFromBin(std::istream&);
	std::ostream& writeToBin(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Schedule&);
	friend std::ostream& operator<<(std::ostream&, const Schedule&);

	void open(std::string);
	void close();
	void save();
	void saveas(std::string);
//	void help();
	void exit();

	bool getIsDone() const;
	bool getIsOpen() const;

	//void book(std::string);//remove
	//void unbook();//remove
	void book(const Arrangement&);
	bool unbook(const Date&, const MeetingTime&); //void
	void agenda(const Date& date);

	void change(const Date&, const Time&, std::string, std::string);

	void change(const Date&, const Time&, const char*, const Date&);	//promenq denq
	void change(const Date&, const Time&, const char*, const Time&);	//start/endtime
	void change(const Date&, const Time&, const char*, const char*);	//note/name

	void find(const char*) const;
	void holiday(const Date&);
	void busydays(const Date&, const Date&) const;
	Date findslot(const Date&, size_t) const;
	Date findslotwith(const Date&, size_t, std::vector<std::string>, size_t) const; //const schedule?
	Date findslotwith(const Date&, size_t, const Schedule*, size_t) const; //const schedule?
	Date findslotwithOneCal(const Date&, size_t, const Schedule&) const; 
	void merge(std::vector<std::string>, size_t);
	void merge(const Schedule*, size_t);
};

#include "Schedule.hpp"

#endif 
