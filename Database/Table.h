#ifndef TABLE_H
#define TABLE_H

#include "IColumn.h"

class Table
{
	size_t size;
	IColumn** cols;

public:
	Table();
	Table(IColumn* [], size_t s);

	void print() const;
	void printTableLine() const;
	void printTableTitles() const;
	void printTableRow() const;
};

#endif
