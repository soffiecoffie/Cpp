#ifndef ICOLUMN__H
#define ICOLUMN__H


class IColumn
{

public:
	virtual void printCellLine() const = 0;
	virtual void printCellTitle() const = 0;
	virtual void printCellInsides(size_t) const = 0;
	virtual void printCell() const = 0;
	virtual size_t getColSize() const = 0;
};

#endif