#include <cstring>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Arrangement.h"

Arrangement::Arrangement(const char* _name, const char* _note, const Date& _day, const MeetingTime& _time) :day(_day), time(_time) //is this ok? op=?copy con?
{
	setName(_name);
	setNote(_note);
}

Arrangement::Arrangement(const Date& d, const MeetingTime& m) : name(nullptr), note(nullptr)
{
	time = m;
	day = d;
}

Arrangement::Arrangement(bool h, const Date& d): holiday(h), day(d), name(nullptr), note(nullptr)
{
}

Arrangement::~Arrangement()
{
	delete[] this->name;
	delete[] this->note;
}

size_t Arrangement::getLength() const
{
	if (!getHoliday()) {
		int hourDifference = getTime().end.getHour() - getTime().start.getHour();
		int minuteDifference = getTime().end.getMinutes() - getTime().start.getMinutes();

		return hourDifference * 60 + minuteDifference;
	}
	
	return 0;
}

void Arrangement::setName(const char* _name)
{
	//delete[] name;
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
}

void Arrangement::setNote(const char* _note)
{
	//delete[] name;
	note = new char[strlen(_note) + 1];
	strcpy(note, _note);
}

void Arrangement::setHoliday(bool h)
{
	holiday = h;
}

void Arrangement::setDate(const Date& d)
{
	day = d;
}

void Arrangement::setStartTime(const Time& t)
{
	assert(t < time.end);
	time.start = t;
}

void Arrangement::setEndTime(const Time& t)
{
	assert(time.start < t);
	time.end = t;
}

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

Arrangement& Arrangement::operator=(const Arrangement& other)
{
	if (this != &other) {
		delete[] name;	//okay?
		delete[] note;
	
		setHoliday(other.getHoliday());

		//when other's name/note is nullptr setName/Note throw exception because i can't strlen(nullptr)
		//therefore i check for nullptr before sending it to the setter
		if (other.getName() != nullptr) setName(other.getName());
		else name = nullptr;

		if (other.getNote() != nullptr) setNote(other.getNote());
		else note = nullptr;

		day = other.getDay();
		time = other.getTime();
	}
	return *this;
}

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
//		holiday = false;
		setHoliday(false);

		setName(temp);

		in.getline(temp, 1024, '\n');
		setNote(temp);

		day.read(in);

		time.start.read(in);
		in.ignore(3, ' - ');
		in >> time.end;
	}

	return in;
}

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

std::istream& Arrangement::readFromBin(std::istream& in)
{
	int num;
	char* temp = new char[1024];

	in >> num;
	in.read(temp, num);
	temp[num] = '\0';

	//std::cout << temp;
	if (num == 3 && strcmp(temp, "(*)") == 0) {
		holiday = true;
		day.read(in);// FromBin(in);
		return in;
	}

	setName(temp);
	
	in >> num;
	in.read(temp, num);
	temp[num] = '\0';
	setNote(temp);

	day.read(in);// FromBin(in);

	time.start.read(in);

	time.end.read(in);

	return in;
}

std::ostream& Arrangement::writeToBin(std::ostream& out) const
{
	if (!holiday) {
		out << strlen(name);

		out.write(name, strlen(name));
		out << '\n';

		out << strlen(note);
		out.write(note, strlen(note));
		out << '\n';

		day.write(out);// ToBin(out);
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

std::istream& operator>>(std::istream& in, Arrangement& a)
{
	a.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Arrangement& a)
{
	a.write(out);
	return out;
}
