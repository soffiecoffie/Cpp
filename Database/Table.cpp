#include "Table.h"
#include <iostream>


Table::Table(): cols(nullptr), size(0)
{
}

Table::Table(IColumn* arr[], size_t s) : size(s)
{
	cols = new IColumn*[s];
	for (size_t i = 0; i < size; ++i)
	{
		cols[i] = arr[i];// new IColumn;				//*arr[i];

	}
}

void Table::print() const
{
	printTableLine();

	printTableTitles();

	//printTableLine();

	printTableRow();

	printTableLine();


}

void Table::printTableLine() const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellLine();
	}
	std::cout << "+\n";
}

void Table::printTableTitles() const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellTitle();
	}
	std::cout << "|\n";
}

void Table::printTableRow() const
{
	size_t max = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (max < cols[i]->getColSize()) max = cols[i]->getColSize();
	}
	size_t colSize = max;

	//if one col is shorter then make cells say NULL		TODO
	for (size_t i = 0; i < max; ++i)
	{
		printTableLine();
		for (size_t j = 0; j < size; ++j)
		{
			cols[j]->printCellInsides(i);
		}
		std::cout << "|\n";
	}
}
