#ifndef DATE_CPP
#define DATE_CPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "Date.h"

/** @brief конструктор по подразбиране*/
Date::Date() : year(2020), month(1), day(1)
{
}

/** @brief конструктор с параметри */
Date::Date(int _year, int _month, int _day)
{
	this->setYear(_year);
	this->setMonth(_month);
	this->setDay(_day);
}

/** @brief връща годината */
int Date::getYear() const
{
	return year;
}

/** @brief връща месеца */
int Date::getMonth() const
{
	return month;
}

/** @brief връща деня */
int Date::getDay() const
{
	return day;
}

/** @brief променя годината */
void Date::setYear(int _year)
{
	//проверява дали подадената година е валидна и ако не е 
	assert(_year > 2010 && _year < 2040);
	this->year = _year;
}

/** @brief променя месеца */
void Date::setMonth(int _month)
{
	//проверява дали подаденият месец е валиден и ако не е спира изпълнението на програмата
	assert(_month > 0 && _month < 13);
	this->month = _month;
}

/** @brief променя деня */
void Date::setDay(int _day)
{
	//проверява дали подаденият ден е валиден и ако не е спира изпълнението на програмата
	assert(_day > 0 && _day <= maxDays());
	this->day = _day;
}

/** @brief принтира датата на екрана */
void Date::print() const
{
	this->write(std::cout);
}

/** @brief връща истина ако датата, с която сме извикали тази функция е преди подадената */
bool Date::operator<(const Date& other) const
{
	if (this->year < other.year) return true;
	else if (this->year > other.year) return false;
	else if (this->month < other.month) return true;
	else if (this->month > other.month) return false;
	else return this->day < other.day;
}

/** @brief връща истина ако датите съвпадат */
bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

/** @brief връща истина ако датата от ляво е преди или в същия ден като датата от дясно */
bool Date::operator<=(const Date& other) const
{
	return operator<(other) || operator==(other);
}

/** @brief връща истина ако годината е високосна */
bool Date::isLeap() const
{
	if (year % 4 == 0)
		return !(year % 100 == 0 && year % 400 != 0);
	return false;
}

/** @brief връща максималният брой дни за съответния месец */
int Date::maxDays() const
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

/** @brief връща датата на следващия ден */
Date Date::getNextDay() const
{
	Date result;
	if ((getDay() + 1) <= maxDays()) result = Date(getYear(), getMonth(), getDay() + 1);
	else {
		if (getMonth() == 12) {
			result = Date(getYear() + 1, 1, 1);
		}
		else {
			result = Date(getYear(), getMonth() + 1, 1);
		}
	}
	return result;
}

/** @brief връща датата от подадения низ */
Date Date::stringToDate(std::string str)
{
	Date result;

	std::string year = str; 
	year.erase(year.begin() + 4, year.end());
	result.setYear(std::stoi(year));

	std::string month = str;
	month.erase(month.begin(), month.begin() + 5);
	month.erase(month.begin() + 2, month.end());
	result.setMonth(std::stoi(month));
	
	std::string day = str;
	day.erase(day.begin(), day.begin() + 8);
	result.setDay(std::stoi(day));
	
	return result;
}

/** @brief прочита дата от файл или стандартния вход */
std::istream& Date::read(std::istream& in)
{
	int num;
	in >> num;
	setYear(num);

	in.ignore(1, '-');
	in >> num;
	setMonth(num);

	in.ignore(1, '-');
	in >> num;
	setDay(num);

	return in;
}

/** @brief записва датата във файл или я извежда на екрана чрез стандартния изход */
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

/** @brief предефинира оператор >> за дати */
std::istream& operator>>(std::istream& in, Date& d)
{
	d.read(in);
	return in;
}

/** @brief предефинира оператор << за дати */
std::ostream& operator<<(std::ostream& out, const Date& d)
{
	d.write(out);
	return out;
}

#endif