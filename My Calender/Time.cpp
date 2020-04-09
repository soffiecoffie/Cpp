#ifndef TIME_CPP
#define TIME_CPP

#include "Time.h"
#include <iostream>
#include <cassert>

Time::Time() : hour(0), minutes(0)
{
}

Time::Time(int _hour, int _minutes)
{
	this->setHour(_hour);
	this->setMinutes(_minutes);
}

int Time::getHour() const
{
	return hour;
}

int Time::getMinutes() const
{
	return minutes;
}

void Time::setHour(int _hour)
{
	assert(_hour >= 0 && _hour <= 23);
	hour = _hour;
}

void Time::setMinutes(int _minutes)
{
	assert(_minutes >= 0 && _minutes <= 59);
	minutes = _minutes;
}

bool Time::operator<(const Time& other) const
{
	if (this->hour == other.hour)return this->minutes < other.minutes;
	return this->hour < other.hour;
}

bool Time::operator==(const Time& other) const
{
	return hour == other.hour && minutes == other.minutes;
}

void Time::print() const
{
	this->write(std::cout);
}

std::ostream& Time::write(std::ostream& out) const
{
	if (hour / 10 == 0)
		out << '0' << hour << ':';
	else
		out << hour << ':';
	if (minutes / 10 == 0)
		out << '0' << minutes;
	else
		out << minutes;

	return out;
}

std::istream& Time::read(std::istream& in)
{
	in >> this->hour;

	int num;
	in.ignore(1, ':');
	in >> num;
	if (num != 0) this->minutes = num;
	else in >> this->minutes;

	return in;
}


std::istream& operator>>(std::istream& in, Time& t)
{
	t.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Time& t)
{
	t.write(out);
	return out;
}

#endif
