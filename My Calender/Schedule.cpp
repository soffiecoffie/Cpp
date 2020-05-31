#include "Schedule.h"
#include "CmdValidator.h"
#include <iostream>
#include <cassert>

/** @brief увеличава големината с n */
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

/** @brief проверява дали даден низ се намира в друг */
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

/** @brief помощна функция за изтриване на динамичната памет */
void Schedule::del()
{
	delete[] arr;
}

/** @brief конструктор с параметри */
Schedule::Schedule(const Arrangement* _arr, size_t _size): size(_size), arr(new Arrangement[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = _arr[i];
	}
}

/** @brief копи конструктор */
Schedule::Schedule(const Schedule& other): Schedule(other.getArr(), other.getSize())
{
}

/** @brief деструктор */
Schedule::~Schedule()
{
	del();
}

/** @brief задава ново име на файла */
void Schedule::setUserFile(std::string str)
{
	userFile = str;
}

/** @brief връща големината */
size_t Schedule::getSize() const
{
	return size;
}

/** @brief връща срещата на дадено място в масива */
Arrangement& Schedule::getArrangement(size_t ind) const
{
	return arr[ind];
}
/** @brief връща масива от срещи в календара */
Arrangement* Schedule::getArr() const
{
	return arr;
}

/** @brief връща индекса, на който се намира някоя среща по нейната дата и начало */
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

/** @brief връща времето заетост за даден ден в минути */
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

/** @brief връща истина, ако незаписана среща се застъпва с друга */
bool Schedule::overlap(const Arrangement& other) const
{
	return overlapOthers(other, -1);
}

/** @brief връща истина, ако подадената среща се застъпва с друга */
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

/** @brief връща срещата, с която се застъпва дадена среща */
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

/** @brief разменя местата на срещи в масив по техните индекси */
void Schedule::swapArrangements(size_t i, size_t j)
{
	Arrangement temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/** @brief сортира масива от срещи хронологично */
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

/** @brief връща истина, ако подадената дата е празник */
bool Schedule::isHoliday(const Date& d) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (d == arr[i].getDay() && arr[i].getHoliday()) return true;
	}
	return false;
}

/** @brief проверява дали има свободно място за среща в даден ден за определено време */
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

/** @brief връща свободно място за среща в даден ден с дадена дължина */
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

/** @brief слива всички календари в един с възможност за застъпване */
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
			arrs[spot++] = cal[i].getArrangement(j);
		}

	}
	return Schedule (arrs, resultSize);
}

/** @brief предефинира оператор = */
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

/** @brief принтира всички срещи в календара */
void Schedule::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "Arrangement " << i + 1 << '\n';
		arr[i].print();
	}
}

/** @brief връща масив от няколко календара от съответните им файлове */
Schedule* Schedule::getCalendars(std::vector<std::string> files) const
{
	Schedule* calendars = new Schedule[files.size()];
	for (size_t i = 0; i < files.size(); i++)
	{
		std::ifstream in(files[i].c_str());
		calendars[i].read(in);
		in.close();
	}
	return calendars;
}

/** @brief прочита календар */
std::istream& Schedule::read(std::istream& in)
{
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

/** @brief записва календар във файл */
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

/** @brief отваря съществуващ календар или създава нов */
void Schedule::open(std::string input)
{
	input = getWord(2, input);
	std::ifstream in(input, std::ios::in);
	if (!in) {
		std::ofstream out(input);
		if (!out) {
			std::cout << "Can't open file " << input << " try again\n"; 
		}
		else {
			write(out);
			setUserFile(input);
			isOpen = 1;
			std::cout << "Successfully created a new file " << input << std::endl;

		}
	}
	else {
		read(in);

		setUserFile(input);

		isOpen = 1;
		std::cout << "Successfully opened file " << input << std::endl;
	}
}

/** @brief затваря календара */
void Schedule::close()
{
	del();
	isDone = 0;
	size = 0;
	isOpen = 0;
	//std::cout << "No changes were made to your calendar.\n";
	std::cout << "Successfully closed file " << userFile << std::endl;
}

/** @brief запазва промените по календара в същия файл */
void Schedule::save()
{
	std::ofstream out(userFile);
	if (!out) {
		std::cout << "Can't open file " << userFile << std::endl;
	}
	else {
		write(out);
		std::cout << "Successfully saved " << userFile << std::endl;
	}
}

/** @brief запазва календара в даден файл */
void Schedule::saveas(std::string input)
{
	//input.erase(0, CmdValidator::getFirstSpaceInd(input) + 1);
	input = getWord(2, input);
	std::ofstream out(input);
	if (!out) {
		std::cout << "Can't save file as" << input << std::endl;
	}
	else {
		write(out);

		std::cout << "Successfully saved as" << input << std::endl;
	}
}

/** @brief прекратява програмата */
void Schedule::exit()
{
	std::cout << "Exiting the program...";
	isDone = 1;
}

/** @brief връща истина, ако потребителят е готов да излезе */
bool Schedule::getIsDone() const
{
	return isDone;
}

/** @brief връща истина, ако потребителят е отворил календар */
bool Schedule::getIsOpen() const
{
	return isOpen;
}

/** @brief запазва нова среща */
void Schedule::book(const Arrangement& other)
{
	if (!this->overlap(other)) { 
		addSize(1);
		arr[size - 1] = other;
	}
	else std::cout << "Times overlap! Can't book.\n";
}

/** @brief отписва среща */
bool Schedule::unbook(const Date& date, const MeetingTime& time) 
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
			delete[] temp;
			return true;
		}
	}
	std::cout << "Nothing was unbooked! \nThere isn't an existing appointment on " << date
		<< " from " << time.start << " to " << time.end << std::endl;
	return false;
}

/** @brief изписва на екрана всички задължения за даден ден хронологично */
void Schedule::agenda(const Date& date)
{
	bool empty = 1;
	if(size)
		sortChronologically();
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i].getDay() == date && arr[i].getHoliday()) {
			std::cout << date << " is a holiday!\n";
			return;
		}
		else if (arr[i].getDay() == date) {
			arr[i].print();
			empty = 0;
		}
	}
	if (empty || size == 0) {
		std::cout << "There's nothing planned on " << date << "!" << std::endl;
		//std::cout << "This command was successful!\n";
	}
	else std::cout << "This command was successful!\n";
}

/** @brief извиква правилната функция за промяна на ден/начално време/край/име/съобщение на среща */
void Schedule::change(const Date& d, const Time& start, std::string option, std::string newvalue)
{
	if (option == "date") {
		Date day = day.stringToDate(newvalue);
		change(d, start, option.c_str(), day);
	}
	else if (option == "starttime" || option == "endtime") {
		Time t = t.stringToTime(newvalue);
		change(d, start, option.c_str(), t);
	}
	else if (option == "note" || option == "name") {
		change(d, start, option.c_str(), newvalue.c_str());
	}
	else std::cout << "Invalid option! Command change was unssuccessful!";
}

/** @brief променя деня на дадена среща */
void Schedule::change(const Date& d, const Time& start, const char* option, const Date& newDate)
{
	assert(strcmp(option, "date") == 0);
	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		std::cout << "Nothing has been changed!\n";
		return;
	}

	arr[ind].setDate(newDate);
}

/** @brief променя началното време или края на дадена среща */
void Schedule::change(const Date& d, const Time& start, const char* option, const Time& newTime)
{
	assert(strcmp(option, "starttime") == 0 || strcmp(option, "endtime") == 0);

	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		std::cout << "Nothing has been changed!\n";
		return;
	}

	if (strcmp(option, "starttime") == 0) {
		if (newTime < arr[ind].getTime().end && !(overlapOthers(Arrangement(d, MeetingTime(newTime, arr[ind].getTime().end)), ind))) {
			arr[ind].setStartTime(newTime);
			std::cout << "Successfully changed the " << option << "!\n";
		}
		else {
			std::cout << "The arrangement on " << d << " at " << start << " can't start at " << newTime << "!\n\n";
			std::cout << "Nothing has been changed!\n";
		}
	}
	else if (arr[ind].getTime().start < newTime && !(overlapOthers(Arrangement(d, MeetingTime(arr[ind].getTime().start, newTime)), ind))) {
		arr[ind].setEndTime(newTime);
		std::cout << "Successfully changed the " << option << "!\n";
	}
	else {
		std::cout << "The arrangement on " << d << " at " << start << " can't end at " << newTime << "!\n\n";
		std::cout << "Nothing has been changed!\n";
	}
}

/** @brief променя среща или име на дадена среща */
void Schedule::change(const Date& d, const Time& start, const char* option, const char* str)
{
	assert(strcmp(option, "note") == 0 || strcmp(option, "name") == 0);

	int ind = findIndex(d, start);
	if (ind == -1) {
		std::cout << "There isn't anything planned on " << d << " at " << start << "!\n\n";
		std::cout << "Nothing has been changed!\n";
		return;
	}

	if (strcmp(option, "note") == 0) {
		std::cout << "Successfully changed the " << option << "!\n";
		arr[ind].setNote(str);
	}
	else {
		arr[ind].setName(str);
		std::cout << "Successfully changed the " << option << "!\n";
	}
}

/** @brief изписва на екрана всички срещи, които съдържат дадена дума в себе си */
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

	if (empty) std::cout << "------NONE------\n\n";

}

/** @brief задава дадения ден като празник и изтрива всички планове от деня, ако има такива */
void Schedule::holiday(const Date& d)
{
	//махам плановете от деня, ако има такива
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

/** @brief изписва на екрана всички дни от дадена дата до друга сортирани по заетост */
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
	
	std::vector<size_t> ind;
	for (size_t i = 0; i < interval.size(); ++i)
	{
		ind.push_back(getBusyMinutes(interval[i]));
	}

	int max;
	for (size_t i = 0; i < interval.size() - 1; ++i)
	{
		max = i;
		for (size_t j = i + 1; j < interval.size(); ++j) {
			if (ind[max] < ind[j]) {
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

/** @brief връща дата, на която има свободно място за среща с определено време на продължителност */
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

/** @brief връща дата, на която има свободно място за среща с определено време на продължителност, съобразено с няколко календара, 
* взети от текстови файлове
*/
Date Schedule::findslotwith(const Date& from, size_t hours, std::vector<std::string> files, size_t sizeCalendars) const
{
	Schedule* calendars = getCalendars(files);
	return findslotwith(from, hours, calendars, sizeCalendars);
}

/** @brief връща дата, на която има свободно място за среща с определено време на продължителност, съобразено с няколко календара */
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
	delete[] allCals;
	return busyHours.findslot(from, hours);
}

/** @brief слива няколко календара от файлове в един */
void Schedule::merge(std::vector<std::string> files, size_t n)
{
	//записва всички календари от съответните файлове в един масив 
	Schedule* calendars = getCalendars(files);
	//слива масивите
	merge(calendars, n);
}

/** @brief слива няколко календара в един */
void Schedule::merge(const Schedule* cals, size_t calSize)
{
	Arrangement newArr;
	for (size_t i = 0; i < calSize; ++i)
	{
		for (size_t j = 0; j < cals[i].getSize(); ++j)
		{
			if (overlap(cals[i].getArrangement(j))) {
				bool okay = true;
				newArr = cals[i].getArrangement(j);
				do {
					std::cout << "These arrangements overlap: \n\nArrangement 1\n";
					newArr.print();
					
					std::cout << "\n\nArrangement 2\n";
					size_t ind = findIndex(getOverlappedArr(cals[i].getArrangement(j)).getDay(), getOverlappedArr(cals[i].getArrangement(j)).getTime().start);
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
					
					std::cin.ignore(1);
					
					if(num==2){
						newArr = arr[ind]; 
						unbook(arr[ind].getDay(), arr[ind].getTime());
						book(cals[i].getArrangement(j));
					}
					else {
						newArr = cals[i].getArrangement(j);
					}
					newArr.setDate(newDate);

					if (newArr.getTime().end < newStart) {		//заради assert-а в set-ърите
						newArr.setEndTime(newEnd);
						newArr.setStartTime(newStart);
					}
					else {
						newArr.setStartTime(newStart);
						newArr.setEndTime(newEnd);
					}

					if (overlap(newArr)) {
						okay = false;
					}
					else {
						okay = true;
						book(newArr);
					}
				} while (!okay);
			}
			else book(cals[i].getArrangement(j));
		}
	}
}

/** @brief предефинира operator>> */
std::istream& operator>>(std::istream& in, Schedule& s)
{
	s.read(in);
	return in;
}

/** @brief предефинира operator<< */
std::ostream& operator<<(std::ostream& out, const Schedule& s)
{
	s.write(out);
	return out;
}
