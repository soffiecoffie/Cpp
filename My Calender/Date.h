#ifndef DATE_H
#define DATE_H
#include <fstream>

class Date {
private:
	int day;
	int month;
	int year;

public:
	Date();
	Date(int, int, int);

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	void setDay(int);
	void setMonth(int);
	void setYear(int);

	void printDate() const;
	bool operator<(const Date&);
	bool operator==(const Date&); //test

	bool isLeap();
	int maxDays();

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;

	friend std::istream& operator>>(std::istream&, Date&);
	friend std::ostream& operator<<(std::ostream&, const Date&);
};


#endif
