#include <cstring>
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

Arrangement::~Arrangement()
{
	delete[] this->name;
	delete[] this->note;
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
	time.start = t;
}

void Arrangement::setEndTime(const Time& t)
{
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
	//char* temp = new char[100];
	//in.getline(temp, 100, '\n');
	//this->setName(temp);

	//delete[] name;//?
	//delete[] note;//?

	//TODO make the read and write methods like the print with ignore for the words you dont need using their length
	this->name = new char[100];
	in.getline(this->name, 100, '\n');

	this->note = new char[1024];
	in.getline(this->note, 1024, '\n');
	//in.getline(this->note, 1024, '\t'); //TODO make it look pretty when the note is long
	//any text above 60 goes down, if the last character on the line is space do nothing, if it's a letter 
	//that is the end of a string think of an idea for the space as to not look ugly 
	//if it ends with a letter that isnt the last add a - and finish the word on the bottom

	this->day.read(in);

	this->time.start.read(in);
	in.ignore(3, ' - ');
	in >> this->time.end;

	return in;
}

std::ostream& Arrangement::write(std::ostream& out) const
{
	out << this->name << '\n'
		<< this->note << '\n';
	this->day.write(out);
	out << '\n';
	this->time.start.write(out);
	out << " - ";
	this->time.end.write(out);

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
