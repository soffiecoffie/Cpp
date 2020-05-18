#ifndef COLUMN_H
#define COLUMN_H
#include <string>
#include "IColumn.h"

template<typename T>
class Column : public IColumn
{
	size_t size;
	std::string title;
	T* cells;
	
public:
	Column(const char*, const T*, size_t);
	
	Column();
	~Column();

	void printCellLine() const;
	void printCellTitle() const;
	void printCellInsides(size_t) const;
	void printCell() const;

	void printPadding(size_t, size_t) const;
	size_t getColSize() const;

//	void setNullCell(size_t);
//	template<typename U>
//	friend void printCentered(const U);

	void addCell(T);
	void setTitle(const char*);
	size_t getCellLength(size_t) const;
	size_t getLongest() const;
	void printMany(const char*, size_t) const; 
	void printCellContents(size_t) const;
	void print() const;
	//void printCentered(T) const;
	//void printCentered(const char*) const;

};

int digits(int);
bool isOdd(int);

#include "Column.hpp" 
#endif
