#include <cstring>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Arrangement.h"

/** @brief конструктор с параметри*/
Arrangement::Arrangement(const char* _name, const char* _note, const Date& _day, const MeetingTime& _time) :day(_day), time(_time)
{
	setName(_name);
	setNote(_note);
}

/** @brief конструктор с параметри*/
Arrangement::Arrangement(const Date& d, const MeetingTime& m) : name(nullptr), note(nullptr)
{
	time = m;
	day = d;
}

/** @brief конструктор с параметри*/
Arrangement::Arrangement(bool h, const Date& d): holiday(h), day(d), name(nullptr), note(nullptr)
{
}

/** @brief деструктор */
Arrangement::~Arrangement()
{
	delete[] this->name;
	delete[] this->note;
}

/** @brief връща дължината на срещата в минути*/
size_t Arrangement::getLength() const
{
	if (!getHoliday()) {
		int hourDifference = getTime().end.getHour() - getTime().start.getHour();
		int minuteDifference = getTime().end.getMinutes() - getTime().start.getMinutes();

		return hourDifference * 60 + minuteDifference;
	}
	
	return 0;
}

/** @brief задава ново име */
void Arrangement::setName(const char* _name)
{
	delete[] name;
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
}

/** @brief задава ново съобщение */
void Arrangement::setNote(const char* _note)
{
	delete[] note;
	note = new char[strlen(_note) + 1];
	strcpy(note, _note);
}

/** @brief задава нова стойност на булевата променлива, която казва дали някой ден е празник */
void Arrangement::setHoliday(bool h)
{
	holiday = h;
}

/** @brief задава нова дата */
void Arrangement::setDate(const Date& d)
{
	day = d;
}

/** @brief задава ново начално време */
void Arrangement::setStartTime(const Time& newtime)
{
	assert(newtime < time.end);
	time.start = newtime;
}

/** @brief задава ново време за края на среща */
void Arrangement::setEndTime(const Time& newtime)
{
	assert(time.start < newtime);
	time.end = newtime;
}

/** @brief извежда срещата на екрана */
void Arrangement::print() const
{
	if (!holiday) {
	std::cout << "Arrangement with: " << this->name << '\n'
		<< "About: " << note << '\n'
		<< "On: ";

	day.print();
	std::cout << '\n' << "Start: ";
	time.start.print();
	std::cout << '\n' << "End: ";
	time.end.print();
	std::cout << "\n\n";
	}
	else {
		day.print();
		std::cout << " is a holiday!";
		std::cout << "\n\n";
	}
}

/** @brief предефиниция на оператор= за срещи*/
Arrangement& Arrangement::operator=(const Arrangement& other)
{
	if (this != &other) {
	
		setHoliday(other.getHoliday());

		//when other's name/note is nullptr setName/Note throw exception because i can't strlen(nullptr)
		if (other.getName() != nullptr) setName(other.getName());
		else name = nullptr;

		if (other.getNote() != nullptr) setNote(other.getNote());
		else note = nullptr;

		day = other.getDay();
		time = other.getTime();
	}
	return *this;
}

/** @brief прочита среща от файл или от стандартния вход */
std::istream& Arrangement::read(std::istream& in)
{
	char* temp = new char[1024];

	std::ios::streampos position = in.tellg();
	in.getline(temp, 1024, '\n');
	if (strncmp(temp, "(*)", 3) == 0) {
		holiday = true;
		in.seekg(0, std::ios::beg);
		in.seekg(position);
		in.ignore(4, ' ');

		day.read(in);
	}
	else {
		setHoliday(false);

		setName(temp);

		in.getline(temp, 1024, '\n');
		setNote(temp);

		day.read(in);

		time.start.read(in);
		in.ignore(3, ' - ');
		in >> time.end;
	}

	delete[] temp;
	return in;
}

/** @brief записва среща във файл или я извежда на екрана */
std::ostream& Arrangement::write(std::ostream& out) const
{
	if (!holiday) {
		out << this->name << '\n'
			<< this->note << '\n';
		this->day.write(out);
		out << '\n';
		this->time.start.write(out);
		out << " - ";
		this->time.end.write(out);
	}
	else {
		out << "(*) ";
		this->day.write(out);
	}

	return out;
}

/** @brief прочита среща от бинарен файл */
std::istream& Arrangement::readFromBin(std::istream& in)
{
	int num;
	char* temp = new char[1024];

	in >> num;
	in.read(temp, num);
	temp[num] = '\0';

	if (num == 3 && strcmp(temp, "(*)") == 0) {
		holiday = true;
		day.read(in);
		return in;
	}

	setName(temp);
	
	in >> num;
	in.read(temp, num);
	temp[num] = '\0';
	setNote(temp);

	day.read(in);

	time.start.read(in);

	time.end.read(in);

	delete[] temp;
	return in;
}

/** @brief записва среща в бинарен файл */
std::ostream& Arrangement::writeToBin(std::ostream& out) const
{
	if (!holiday) {
		out << strlen(name);

		out.write(name, strlen(name));
		out << '\n';

		out << strlen(note);
		out.write(note, strlen(note));
		out << '\n';

		day.write(out);
		out << '\n';

		time.start.write(out);
		out << '\n';

		time.end.write(out);
	}
	else {
		out << 3;
		out.write("(*)", 3);
		out << '\n';

	}
	
	return out;
}

/** @brief предефиниция на оператор>> за срещи*/
std::istream& operator>>(std::istream& in, Arrangement& a)
{
	a.read(in);
	return in;
}

/** @brief предефиниция на оператор<< за срещи*/
std::ostream& operator<<(std::ostream& out, const Arrangement& a)
{
	a.write(out);
	return out;
}
