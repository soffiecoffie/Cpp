#ifndef DATE_H
#define DATE_H
#include <fstream>

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date();
	Date(int, int, int);

	int getYear() const;
	int getMonth() const;
	int getDay() const;

	void setYear(int);
	void setMonth(int);
	void setDay(int);

	void print() const;
	bool operator<(const Date&) const;
	bool operator==(const Date&) const; //test

	bool isLeap() const;
	int maxDays() const;

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Date&);
	friend std::ostream& operator<<(std::ostream&, const Date&);
};


#endif
