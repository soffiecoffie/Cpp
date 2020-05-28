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
	void addSpace();

public:
	Column(const std::string&, const std::string&, const T*, size_t);
	Column(const char*);
	Column(const Column&) = delete;
	Column();

	~Column();

	size_t getCellLength(size_t) const;

	std::ostream& printCellLine(std::ostream&) const;
	std::ostream& printCellTitle(std::ostream&) const;
	std::ostream& printCellContents(size_t, std::ostream&) const;

	std::ostream& printPadding(size_t, std::ostream&) const;

	size_t getColSize() const;
	std::string getType() const;
	std::string getTitle() const;
	std::string getCellAt(size_t) const;
	T** getCells() const;
	
	void addCell(std::string);

	void setTitle(const std::string&);
	void setCells(const T*, size_t);
	void setType(const std::string&);
	size_t getLongest() const;
	void print() const;
	void setNullCellAt(size_t);
};

#include "Column.hpp" 
#endif
