#ifndef COLUMN_H
#define COLUMN_H
#include <string>
#include "IColumn.h"

template<typename T>
class Column : public IColumn
{
	size_t size;
	T** cells;
	std::string title;
	std::string type;

private:
	void del();
	void addSpace();		//added
	void copyOtherCells(const IColumn&);

public:
	Column(const std::string&, const std::string&, const T*, size_t);
	Column(const std::string&, const std::string&, const T**, size_t); //added
	Column(const char*);
	Column(const std::string&, const std::string&, size_t);
	Column(const Column<T>&);
	Column();

	~Column();

	size_t getCellLength(size_t) const;

	std::ostream& printCellLine(std::ostream&) const;
	std::ostream& printCellTitle(std::ostream&) const;
	std::ostream& printCellContents(size_t, std::ostream&) const;

	std::ostream& printPadding(size_t, std::ostream&) const;

	size_t getRowSize() const;
	std::string getType() const;
	std::string getTitle() const;
	std::string getCellAt(size_t) const;
	T** getCells() const;
	


	void addCell(std::string);//added

	void setTitle(const std::string&);
	void setCells(const T*, size_t);
	void setCells2(const T**, size_t);//added
	void setType(const std::string&);
	size_t getLongest() const;
	void print() const;
	void setNullCellAt(size_t);
};

#include "Column.hpp" 
#endif
/*

#ifndef COLUMN_H
#define COLUMN_H
#include <string>
#include "IColumn.h"

template<typename T>
class Column : public IColumn
{

	size_t size;
	T* cells;		//TODO MAKE A CLASS SO ISNULL CAN HAPPEN
	std::string title;
	std::string type;

public:
	Column(const std::string&, const std::string&, const T*, size_t);
	Column(const char*);
	Column();
	Column(const Column&);//test

	~Column();

	size_t getCellLength(size_t) const;

	std::ostream& printCellLine(std::ostream&) const;
	std::ostream& printCellTitle(std::ostream&) const;
	std::ostream& printCellContents(size_t, std::ostream&) const;

	std::ostream& printMany(const char*, size_t, std::ostream&) const;
	std::ostream& printPadding(size_t, std::ostream&) const;

//	std::string removePaddingFromStr(std::string); //когато чета колоната думата която записвам има
//											//празно място от двете страни за центриране което не трябва да има
//	bool isSpaceBetweenWords(std::string, size_t);
											//void printPadding(size_t, size_t) const;
	size_t getColSize() const;
	std::string getType() const;
	std::string getTitle() const;
	std::string getCellAt(size_t) const;
	T* getCells() const;

	void addCell(std::string);

	void setTitle(std::string);
	void setType(const char*);
	size_t getLongest() const;
	void printCell(size_t) const;
	void print() const;
	int digits(int) const;
	bool isOdd(int) const;
	void setNullCellAt(size_t);
};

	//	template<typename U>
	//	friend void printCentered(const U);

#include "Column.hpp"
#endif


*/