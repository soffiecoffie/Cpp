#ifndef DATE_CPP
#define DATE_CPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "Date.h"

Date::Date() : day(1), month(1), year(2020)
{
}

Date::Date(int _day, int _month, int _year)
{
	this->setYear(_year);
	this->setDay(_day);
	this->setMonth(_month);
}

int Date::getDay() const
{
	return day;
}

int Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}

void Date::setDay(int _day)
{
	assert(_day > 0 && _day < maxDays());
	this->day = _day;
}

void Date::setMonth(int _month)
{
	assert(_month > 0 && _month < 13);
	this->month = _month;
}

void Date::setYear(int _year)
{
	assert(_year > 1920 && _year < 2100);		//is the time frame adequate
	this->year = _year;
}

void Date::printDate() const
{
	this->write(std::cout);
}

bool Date::operator<(const Date& other) const
{
	if (this->year < other.year) return true;
	else if (this->year > other.year) return false;
	else if (this->month < other.month) return true;
	else if (this->month > other.month) return false;
	else return this->day < other.day;
}

bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

bool Date::isLeap() const
{
	if (year % 4 == 0)
		return !(year % 100 == 0 && year % 400 != 0);
	return false;
}


int Date::maxDays() const //is this the best optimization?
{		
	switch (this->month) {
	case 2:
		return (isLeap()) ? 29 : 28;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	}
}

std::istream& Date::read(std::istream& in)
{
	in >> this->year;

	in.ignore(1, '-');
	int num;
	in >> num;
	if (num != 0) this->month = num;
	else in >> this->month;

	in.ignore(1, '-');
	in >> num;
	if (num != 0) this->day = num;
	else in >> this->day;

	return in;
}

std::ostream& Date::write(std::ostream& out) const
{
	out << this->year << '-';
	if (month / 10 == 0)
		out << "0" << month << '-';
	else
		out << month << '-';
	if (day / 10 == 0)
		out << "0" << day;
	else
		out << day;
	return out;
}


std::istream& operator>>(std::istream& in, Date& d)
{
	d.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Date& d)
{
	d.write(out);
	return out;
}



#endif
