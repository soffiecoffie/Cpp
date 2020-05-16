#include "Schedule.h"
#include <iostream>
#include <cassert>
#include <vector>

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
	int ind;
	size_t i = 0;
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

Schedule::Schedule(const Arrangement* _arr, size_t _size): size(_size), arr(new Arrangement[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = _arr[i];
	}
}

size_t Schedule::getSize() const
{
	return size;
}

Arrangement& Schedule::getArrangement(size_t ind) const
{
	return arr[ind];
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

size_t Schedule::getBusyMinutes(const Date& d) const
{
	int length = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == d) {
			length += arr[i].getLength();
		}
	}
	return length;
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

Arrangement& Schedule::getOverlappedArr(const Arrangement& other) const
{
	assert(overlap(other));
	for (size_t i = 0; i < size; ++i)
	{
		if ((arr[i].getDay() == other.getDay()) && (arr[i].getTime().start == other.getTime().start
			|| (arr[i].getTime().start < other.getTime().end && other.getTime().start < arr[i].getTime().start)
			|| (other.getTime().start < arr[i].getTime().end && arr[i].getTime().start < other.getTime().start)))
		{
			return arr[i];
		}
	}
}

void Schedule::swapArrangements(size_t i, size_t j)
{
	Arrangement temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void Schedule::sortChronologically()
{
	int min;
	for (size_t i = 0; i < size - 1; ++i) {
		min = i;

		for (size_t j = i + 1; j < size; ++j) {
			if (arr[j].getDay() < arr[min].getDay() 
				|| (arr[j].getDay() == arr[min].getDay() && arr[j].getTime().start < arr[min].getTime().start)) {
				min = j;
			}
		}
		swapArrangements(min, i);
	}
}

bool Schedule::isHoliday(const Date& d) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (d == arr[i].getDay() && arr[i].getHoliday()) return true;
	}
	return false;
}

bool Schedule::hasFreeSlot(const Date& d, size_t hours) const
{
	int h = 8, m = 0;
	if (!isHoliday(d)) {
		do {
			if (overlap(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m))))) {
				h = getOverlappedArr(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m)))).getTime().end.getHour();
				m = getOverlappedArr(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m)))).getTime().end.getMinutes();
			}
			else return true;
		} while (h <= 16 && h + hours <= 16 && m <= 59);
	}

	return false;
}

MeetingTime Schedule::getFreeSlot(const Date& d, size_t hours) const
{
	assert(hasFreeSlot(d, hours));
	int h = 8, m = 0;
	do {
		if (overlap(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m))))) {
			h = getOverlappedArr(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m)))).getTime().end.getHour();
			m = getOverlappedArr(Arrangement(d, MeetingTime(Time(h, m), Time(h + hours, m)))).getTime().end.getMinutes();
		}
		else return MeetingTime(Time(h, m), Time(h + hours, m));
	} while (h <= 16 && h + hours <= 16 && m <= 59);
}

Schedule Schedule::allBusyHours(const Schedule* cal, size_t calSize) const
{
	size_t resultSize = 0;
	for (size_t i = 0; i < calSize; ++i)
	{
		resultSize += cal[i].getSize();
	}


	Arrangement* arrs = new Arrangement[resultSize];
	size_t spot = 0;
	for (size_t i = 0; i < calSize; ++i)
	{
		for (size_t j = 0; j < cal[i].getSize(); ++j)
		{
			arrs[spot] = cal[i].getArrangement(j);
		}

	}
	return Schedule (arrs, resultSize);
}

Schedule& Schedule::operator=(const Schedule& other)
{
	if (this != &other) {
		size = other.getSize();
		
		delete[] arr;
		arr = new Arrangement[size];
		for (size_t i = 0; i < size; ++i)
		{
			arr[i] = other.getArrangement(i);
		}
	}
	return *this;
}

void Schedule::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "Arrangement " << i + 1 << '\n';
		arr[i].print();
	}
}

std::istream& Schedule::read(std::istream& in)
{
	char* temp = new char[50];
	size_t num;
	in.ignore(100, '\n');
	in.ignore(22);
	in >> num;
	size = num;
	in.ignore(50, '\n');//\n');
	in.ignore(1);
	arr = new Arrangement[size];
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].read(in);
		in.ignore(2, '\n\n');
	}

	return in;
}

std::ostream& Schedule::write(std::ostream& out) const
{
	out << "Welcome to your personal calendar!\n"
		<< "These are all of your " << size << " arrangements: \n\n";
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].write(out);
		out << "\n\n";
	}
	return out;
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

void Schedule::agenda(const Date& date) 
{
	bool empty = 1;
	std::cout << "Agenda for the day " << date << ":\n\n";
	sortChronologically();
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == date && arr[i].getHoliday()) {
			std::cout << date << " is a holiday!\n";
			return;
		}
		else if (arr[i].getDay() == date) {
			arr[i].print();
			std::cout << "________________________________________\n\n\n";
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
	std::vector<Date> interval;

	Date add;
	interval.push_back(from);
	do {
		add = interval[interval.size() - 1].getNextDay();
		interval.push_back(add);
	} while (add < to);

	std::cout << "All days from " << from << " to " << to << " sorted by busyness: \n\n";
	
	size_t* ind = new size_t[interval.size()];
	for (size_t i = 0; i < interval.size(); ++i)
	{
		ind[i] = getBusyMinutes(interval[i]);
	}

	int max;
	for (size_t i = 0; i < interval.size() - 1; ++i)
	{
		max = i;
		for (size_t j = i + 1; j < interval.size(); ++j) {
			if (ind[i] < ind[j]) {
				max = j;
			}
		}
		std::swap(interval[i], interval[max]);
		std::swap(ind[i], ind[max]);
	}

	for (size_t i = 0; i < interval.size(); i++)
	{
		std::cout << interval[i] << std::endl;
	}
}

Date Schedule::findslot(const Date& from, size_t hours) const
{
	Date d;
	d = from;
	do {
		if (hasFreeSlot(d, hours)) {
			return d;
		}
		else d = d.getNextDay();
	} while (true);
}

Date Schedule::findslotwith(const Date& from, size_t hours, const Schedule* calendars, size_t sizeCalendars) const
{
	Schedule* allCals = new Schedule[sizeCalendars + 1];
	for (size_t i = 0; i < sizeCalendars ; ++i)
	{
		allCals[i] = calendars[i];
	}
	allCals[sizeCalendars] = *this;

	Schedule busyHours;
	busyHours = allBusyHours(allCals, sizeCalendars + 1);

	return busyHours.findslot(from, hours);
}

//remove?
Date Schedule::findslotwithOneCal(const Date& from, size_t hours, const Schedule& cal) const
{
	Date d, temp;
	temp = from;
	do {
		d = findslot(temp, hours);
		if (cal.hasFreeSlot(d, hours)) {
			if (getFreeSlot(d, hours) == cal.getFreeSlot(d, hours)) {
				return d;
			}
		}
		else {
			temp = d;
		}
	} while (true);
}

void Schedule::merge(const Schedule* cals, size_t calSize)
{
	Arrangement newArr;
	for (size_t i = 0; i < calSize; ++i)
	{
		for (size_t j = 0; j < cals[i].getSize(); ++j)
		{
			//only works if 2 arrangements at most overlap
			if (overlap(cals[i].getArrangement(j))) {
				bool okay = true;
				newArr = cals[i].getArrangement(j);
				do {
					std::cout << "These arrangements overlap: \n\n Arrangement 1\n";
					//cals[i].getArrangement(j).print();
					newArr.print();
					
					std::cout << "\n\nArrangement 2\n";
					//temp = getOverlappedArr(cals[i].getArrangement(j));
					size_t ind = findIndex(getOverlappedArr(cals[i].getArrangement(j)).getDay(),
						getOverlappedArr(cals[i].getArrangement(j)).getTime().start);
					arr[ind].print();

					int num;
					do {
						std::cout << "\nEnter the number of the arrangement you would like to move: \n";
						std::cin >> num;
					} while (num != 1 && num != 2);

					Date newDate;
					std::cout << "Enter your preffered day for the arrangement: \n";
					std::cin >> newDate;

					Time newStart;
					std::cout << "Enter your preffered start time for the arrangement: \n";
					std::cin >> newStart;

					Time newEnd;
					std::cout << "Enter your preffered end time for the arrangement: \n";
					std::cin >> newEnd;

					//if (num == 1) {
					//	newArr = cals[i].getArrangement(j);
					//}
					//else {
					if(num==2){
						newArr = arr[ind]; //temp;
						unbook(arr[ind].getDay(), arr[ind].getTime());
						book(cals[i].getArrangement(j));
					}
					newArr.setDate(newDate);
					newArr.setStartTime(newStart);
					newArr.setEndTime(newEnd);

					if (overlap(newArr)) {
						okay = false;
					}
					else okay = true;

				} while (!okay);
			}
			else book(cals[i].getArrangement(j));
		}
	}
}

std::istream& operator>>(std::istream& in, Schedule& s)
{
	s.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Schedule& s)
{
	s.write(out);
	return out;
}
