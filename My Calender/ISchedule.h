#ifndef ISCHEDULE_H
#define ISCHEDULE_H

#include <string>
#include <vector>
#include "Arrangement.h"

/** @brief клас ISchedule е интерфейсен клас на Schedule */
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

	virtual ~ISchedule() = 0 {};

	virtual void book(const Arrangement&) = 0;
	virtual bool unbook(const Date&, const MeetingTime&) = 0; //void
	virtual void holiday(const Date&) = 0;
	virtual void busydays(const Date&, const Date&) const = 0;
	virtual void change(const Date&, const Time&, std::string, std::string) = 0;
	virtual void find(const char*) const = 0;
	virtual Date findslot(const Date&, size_t) const = 0;
	virtual Date findslotwith(const Date&, size_t, std::vector<std::string>, size_t) const = 0; 
	virtual void merge(std::vector<std::string>, size_t) = 0;
	virtual void agenda(const Date& date) = 0;
};

#endif
