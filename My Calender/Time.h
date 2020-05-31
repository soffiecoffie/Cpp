#ifndef TIME_H
#define TIME_H
#include <fstream>
#include <string>

/** @brief клас Time създава време*/
class Time
{
	int hour;
	int minutes;

public:
	Time();
	Time(int, int);

	int getHour() const;
	int getMinutes() const;

	void setHour(int);
	void setMinutes(int);

	bool operator<(const Time&) const;
	bool operator==(const Time&) const; 
	Time& operator=(const Time&);

	void print() const;
	Time stringToTime(std::string) const;

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Time&);
	friend std::ostream& operator<<(std::ostream&, const Time&);
};


#endif