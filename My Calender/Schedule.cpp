#include "Schedule.h"
#include <iostream>

Schedule::Schedule(Arrangement* _arr, size_t _size)
{
	size = _size;
	arr = new Arrangement[size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = _arr[i];
	}
}

void Schedule::book(const Arrangement& other)
{
	if (!this->overlap(other)) { //okay brackets?
		++size;
		arr[size - 1] = other;
	}
	else std::cout << "Times overlap! Can't book.\n";
}

void Schedule::unbook(const Date& date, MeetingTime time) ///is this working?
{
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == date && arr[i].getTime().start == time.start && arr[i].getTime().end == time.end) {
			size_t ind = i;
			for (ind; ind < size - 1; ++ind)
			{
				arr[ind] = arr[ind + 1];
			}
			--size;
			return;
		}
	}
}

bool Schedule::overlap(const Arrangement other) const
{
	for (size_t i = 0; i < size; i++)
	{ 
		if ((arr[i].getDay() == other.getDay()) && (arr[i].getTime().start == other.getTime().start
				|| (arr[i].getTime().start < other.getTime().end && other.getTime().start < arr[i].getTime().start)
				|| (other.getTime().start < arr[i].getTime().end && arr[i].getTime().start < other.getTime().start))) return true;
	}
	return false;
}

void Schedule::print() const
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << "Arrangement " << i + 1<<'\n';//yes?
		arr[i].print();
		std::cout << '\n';
	}
}

void Schedule::agenda(const Date& date) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i].getDay() == date) {
			arr[i].print();
			std::cout << "\n_______________________________________\n\n";
		}
	}
}
