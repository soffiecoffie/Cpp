#include "Schedule.h"
#include <iostream>
#include <cassert>

//увеличава големината в зависимост от подадената големина
void Schedule::addSize(size_t n)
{
	Arrangement* temp = new Arrangement[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = new Arrangement[size + n];
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = temp[i];
	}
	size += n;
	
	delete[] temp;
}

//проверява дали даден низ се намира в друг
bool Schedule::hasStr(const char* original, const char* str) const
{
	int count = 0;
	int ind, i = 0;
	if (strlen(str) > strlen(original)) return false;

	for (size_t j = 0; j < strlen(str); )
	{
		if (i >= strlen(original)) break;
		if (count == 0) ind = i;
		if (original[i] == str[j]) {
			++count;
			if (count == strlen(str)) return true;
			if (count == 1) ind = i;
			++i;
			++j;
		}
		else {
			count = 0;
			i = ++ind;
			j = 0;
		}
	}
	return false;
}

Schedule::Schedule(Arrangement* _arr, size_t _size): size(_size), arr(new Arrangement[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = _arr[i];
	}
}

int Schedule::findIndex(const Date& d, const Time& start)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == d && arr[i].getTime().start == start) {
			return i;
		}
	}
	return -1;
}

int Schedule::getBusyHours(const Date& d) const
{
	//Dumb questions:
	//kakva trqbva da e tochnostta
	//kolko chasa rabota ima za celiq den t.e - 15:59-17:01 - shte e floor(1chas i 2 min)=1chas 
	//ili kolko chasa ot denq imat zaetost t.e - 15:59-17:01 - shte sa 3
	return 0;
}

bool Schedule::overlap(const Arrangement& other) const
{
	return overlapOthers(other, -1);
}

bool Schedule::overlapOthers(const Arrangement& other, int ind) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (i != ind) {
			if ((arr[i].getDay() == other.getDay()) && (arr[i].getTime().start == other.getTime().start
				|| (arr[i].getTime().start < other.getTime().end && other.getTime().start < arr[i].getTime().start)
				|| (other.getTime().start < arr[i].getTime().end && arr[i].getTime().start < other.getTime().start))) return true;
		}
	}

	return false;
}

void Schedule::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "Arrangement " << i + 1 << '\n';//yes?
		arr[i].print();
//		std::cout << '\n';
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
			for (size_t i = 0; i < size; ++i)
			{
				temp[i] = arr[i];
			}

			delete[] arr;
			arr = new Arrangement[size];
			for (size_t i = 0; i < size; ++i)
			{
				arr[i] = temp[i];
			}
			return;
		}
	}
}

void Schedule::agenda(const Date& date) const
{
	bool empty = 1;
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == date && arr[i].getHoliday()) {
			std::cout << date << " is a holiday!\n";
			return;
		}
		else if (arr[i].getDay() == date) {
			arr[i].print();
			std::cout << "_______________________________________\n\n\n";
			empty = 0;
		}
	}
	if (empty) {
		std::cout << "There's nothing planned on " << date << "." << std::endl;
	}
}

void Schedule::change(const Date& d, const Time& start, const char* option, const Date& newDate)
{
	assert(strcmp(option, "date") == 0);
	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		return;
	}

	arr[ind].setDate(newDate);
}

void Schedule::change(const Date& d, const Time& start, const char* option, const Time& newTime)
{
	assert(strcmp(option, "starttime") == 0 || strcmp(option, "endtime") == 0);

	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		return;
	}

	if (strcmp(option, "starttime") == 0) {
		if (newTime < arr[ind].getTime().end && !(overlapOthers(Arrangement(d, MeetingTime(newTime, arr[ind].getTime().end)), ind)))
			arr[ind].setStartTime(newTime);
		else std::cout << "The arrangement on " << d << " at " << start << " can't start at " << newTime << "!\n\n";
	}
	else if (arr[ind].getTime().start < newTime && !(overlapOthers(Arrangement(d, MeetingTime(arr[ind].getTime().start, newTime)), ind)))
		arr[ind].setEndTime(newTime);
	else std::cout << "The arrangement on " << d << " at " << start << " can't end at " << newTime << "!\n\n";

}

void Schedule::change(const Date& d, const Time& start, const char* option, const char* str)
{
	assert(strcmp(option, "note") == 0 || strcmp(option, "name") == 0);

	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		return;
	}

	if (strcmp(option, "note") == 0) {
		arr[ind].setNote(str);
	}
	else arr[ind].setName(str);
}

void Schedule::find(const char* str) const
{
	std::cout << "All arrangements containing - \"" << str << "\" are: \n\n";
	bool empty = 1;

	for (size_t i = 0; i < size; ++i)
	{
		if (hasStr(arr[i].getName(), str) || hasStr(arr[i].getNote(), str)) {
			arr[i].print();
			empty = 0;
		}
	}

	if (empty) std::cout << "------NONE------";

}

void Schedule::holiday(const Date& d)
{
	//if i've already made plans for the day i'll remove them
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == d) {
			unbook(arr[i].getDay(), arr[i].getTime());
			--i;
		}
	}

	book(Arrangement(d, MeetingTime(Time(0, 0), Time(23, 59))));
	arr[size - 1].setHoliday(true);

}

void Schedule::busydays(const Date& from, const Date& to) const
{
	//TODO
}
