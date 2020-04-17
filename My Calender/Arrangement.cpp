#include "Arrangement.h"
#include <cstring>
#include <iostream>
#include <fstream>

Arrangement::Arrangement(const char* _name, const char* _note, Date _day, MeetingTime _time)
{
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);

	note = new char[strlen(_note) + 1];
	strcpy(note, _note);

	day = _day;
	time = _time; //do i need oper= ? 
}

Arrangement::~Arrangement()
{
	delete[] this->name;
	delete[] this->note;
}

void Arrangement::setName(const char* _name)
{
	delete[] name; //?
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
}

void Arrangement::setNote(const char* _note)
{
	delete[] name;
	note = new char[strlen(_note) + 1];
	strcpy(note, _note);
}

void Arrangement::print() const
{
	std::cout << "Arrangement with: " << this->name << '\n'
		<< "About: " << note << '\n'
		<< "On: ";

	day.printDate();
	std::cout << '\n' << "Start: ";
	time.start.print();
	std::cout << '\n' << "End: ";
	time.end.print();
}

std::istream& Arrangement::read(std::istream& in)
{
	//char* temp = new char[100];
	//in.getline(temp, 100, '\n');
	//this->setName(temp);

	this->name = new char[100];
	in.getline(this->name, 100, '\n');

	this->note = new char[1024];
	in.getline(this->note, 1024, '\n');

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
