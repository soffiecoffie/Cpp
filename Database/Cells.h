#ifndef CELLS__H
#define CELLS__H

template<typename T>
class Cells
{
	T cell;
	bool isNULL = 0;

	int digits(int) const;

public:
	Cells(const T&);
	Cells() = delete;					//ADDED
	Cells(const Cells&) = delete;		//ADDED
	void setNull();
	T getCell() const;

	size_t getCellLength() const;
};

#include "Cells.hpp"
#endif
