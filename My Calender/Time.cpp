#ifndef TIME_CPP
#define TIME_CPP

#include "Time.h"
#include <iostream>
#include <cassert>

/** @brief конструктор по подразбиране */
Time::Time() : hour(0), minutes(0)
{
}


/** @brief конструктор с параметри */
Time::Time(int _hour, int _minutes)
{
	this->setHour(_hour);
	this->setMinutes(_minutes);
}

/** @brief връща часа */
int Time::getHour() const
{
	return hour;
}

/** @brief връща минутите */
int Time::getMinutes() const
{
	return minutes;
}

/** @brief променя часа */
void Time::setHour(int _hour)
{
	//проверява дали подаденият час е валиден и ако не е прекратява програмата 
	assert(_hour >= 0 && _hour <= 23);
	hour = _hour;
}

/** @brief променя минутите */
void Time::setMinutes(int _minutes)
{
	//проверява дали подаденити минути са валидни и ако не са прекратява програмата 
	assert(_minutes >= 0 && _minutes <= 59);
	minutes = _minutes;
}

/** @brief проверява дали времето е по-рано от подаденото */
bool Time::operator<(const Time& other) const
{
	if (this->hour == other.hour)return this->minutes < other.minutes;
	return this->hour < other.hour;
}

/** @brief проверява дали времето съвпада с подаденото */
bool Time::operator==(const Time& other) const
{
	return hour == other.hour && minutes == other.minutes;
}

/** @brief предефинира оператор == */
Time& Time::operator=(const Time& other) 
{
	if (this != &other) {
		setHour(other.getHour());
		setMinutes(other.getMinutes());
	}
	return *this;
}

/** @brief принтира времето на екрана */
void Time::print() const
{
	this->write(std::cout);
}

/** @brief връща време от подаден низ */
Time Time::stringToTime(std::string str) const
{
	Time result;
	std::string h = str;
	h.erase(h.begin() + 2, h.end());
	result.setHour(std::stoi(h));

	std::string m = str;
	m.erase(m.begin(), m.end() - 2);
	result.setMinutes(std::stoi(m));

	return result;
}

/** @brief записва времето във файл или го извежда на екрана чрез стандартния изход */
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

/** @brief прочита времето от стандартния изход или от файл */
std::istream& Time::read(std::istream& in)
{
	int num;
	in >> num;
	setHour(num);

	in.ignore(1, ':');
	in >> num;
	setMinutes(num);

	return in;
}

/** @brief предефинира оператор >> */
std::istream& operator>>(std::istream& in, Time& t)
{
	t.read(in);
	return in;
}

/** @brief предефинира оператор << */
std::ostream& operator<<(std::ostream& out, const Time& t)
{
	t.write(out);
	return out;
}

#endif