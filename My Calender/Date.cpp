#ifndef DATE_CPP
#define DATE_CPP

#include <iostream>
#include <cassert>
#include <fstream>
#include "Date.h"

//конструктор по подразбиране
Date::Date() : year(2020), month(1), day(1)
{
}

//конструктор с параметри
Date::Date(int _year, int _month, int _day)
{
	this->setYear(_year);
	this->setMonth(_month);
	this->setDay(_day);
}

//връща годината
int Date::getYear() const
{
	return year;
}

//връща месеца
int Date::getMonth() const
{
	return month;
}

//връща деня
int Date::getDay() const
{
	return day;
}

//променя годината
void Date::setYear(int _year)
{
	//проверява дали подадената година е валидна и ако не е прекратява програмата
	assert(_year > 1920 && _year < 2100);							//is the time frame adequate
	this->year = _year;
}

//променя месеца
void Date::setMonth(int _month)
{
	//проверява дали подаденият месец е валиден и ако не е прекратява програмата
	assert(_month > 0 && _month < 13);
	this->month = _month;
}

//променя деня
void Date::setDay(int _day)
{
	//проверява дали подаденият ден е валиден и ако не е прекратява програмата
	assert(_day > 0 && _day < maxDays());
	this->day = _day;
}

//принтира датата на екрана
void Date::print() const
{
	this->write(std::cout);
}

//връща истина ако датата, с която сме извикали тази функция е по-ранна от подадената
bool Date::operator<(const Date& other) const
{
	if (this->year < other.year) return true;
	else if (this->year > other.year) return false;
	else if (this->month < other.month) return true;
	else if (this->month > other.month) return false;
	else return this->day < other.day;
}

//връща истина ако датите съвпадат
bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

//връща истина ако годината е високосна
bool Date::isLeap() const
{
	if (year % 4 == 0)
		return !(year % 100 == 0 && year % 400 != 0);
	return false;
}

//връща максималният брой дни за съответния месец
int Date::maxDays() const
{												//is this the best optimization?
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

//прочита дата
std::istream& Date::read(std::istream& in)
{
	int num;
	in >> num;
	setYear(num);

	in.ignore(1, '-');
	in >> num;
	if (num == 0) in >> num;
	setMonth(num);

	in.ignore(1, '-');
	in >> num;
	if (num == 0) in >> num;
	setDay(num);

	return in;
}

//записва датата
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

//предефинира оператор >> и го прочита 
std::istream& operator>>(std::istream& in, Date& d)
{
	d.read(in);
	return in;
}

//предефинира оператор << и го записва
std::ostream& operator<<(std::ostream& out, const Date& d)
{
	d.write(out);
	return out;
}

#endif
