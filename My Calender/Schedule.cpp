#include "Schedule.h"
#include <iostream>

//увеличава големината в зависимост от подадената големина
void Schedule::addSize(size_t n)
{
	Arrangement* temp = new Arrangement[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = new Arrangement[size + n];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = temp[i];
	}
	size += n;
	
	delete[] temp;
}

Schedule::Schedule(Arrangement* _arr, size_t _size): size(_size), arr(new Arrangement[size])
{
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = _arr[i];
	}
}

void Schedule::book(const Arrangement& other)
{
	if (!this->overlap(other)) { 
		addSize(1);
		arr[size - 1] = other;
	}
	else std::cout << "Times overlap! Can't book.\n";
}

void Schedule::unbook(const Date& date, MeetingTime time)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == date && arr[i].getTime().start == time.start && arr[i].getTime().end == time.end) {
			size_t ind = i;
			for (ind; ind < size - 1; ++ind)
			{
				arr[ind] = arr[ind + 1];
			}

			Arrangement* temp = new Arrangement[--size];
			for (size_t i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}

			delete[] arr;
			arr = new Arrangement[size];
			for (size_t i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
			return;
		}
	}
}

bool Schedule::overlap(const Arrangement& other) const
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
		std::cout << "Arrangement " << i + 1 << '\n';//yes?
		arr[i].print();
//		std::cout << '\n';
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
