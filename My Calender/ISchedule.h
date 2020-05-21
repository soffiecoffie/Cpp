#ifndef ISCHEDULE_H
#define ISCHEDULE_H

#include <string>
#include "Arrangement.h"

class ISchedule
{
public:
	virtual void open(std::string) = 0;
	virtual void close() = 0;
	virtual void save() = 0;
	virtual void saveas(std::string) = 0;
	virtual void exit() = 0;
	virtual void help();
	
	virtual bool getIsDone() const = 0;
	virtual bool getIsOpen() const = 0;

	//virtual Destructor needed??

	//virtual void book(const Arrangement&) = 0;
	//virtual void unbook(const Date&, MeetingTime) = 0;
//	template <typename T>
//	virtual void change() = 0;
	//virtual void agenda(const Date& date)= 0;
	//virtual void holiday(const Date&) = 0;
	//virtual void busydays(const Date&, const Date&) const = 0;
	//virtual void find(const char*) const = 0;
	//virtual Date findslot(const Date&, size_t) const = 0;
	//virtual Date findslotwith(const Date&, size_t, const Schedule*, size_t) const = 0;
	//virtual void merge(const Schedule*, size_t) = 0;
	
	virtual void book(const Arrangement&) = 0;
	virtual void unbook(const Date&, const MeetingTime&) = 0;
	//virtual void change() = 0;
	//virtual void agenda() = 0;
	//virtual void holiday() = 0;
	//virtual void busydays() = 0;
	//virtual void find() = 0;
	//virtual void findslot() = 0;
	//virtual void findslotwith() = 0;
	//virtual void merge() = 0;
};


#endif