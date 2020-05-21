#include <iomanip>
#include <iostream>
#include <cassert>
#include "Column.h"

template<typename T>
Column<T>::Column(const std::string& _title, const std::string& _type, const T* _cells, size_t _size) : size(_size), cells(new T[_size])
{
	title = _title;
	type = _type;
	
	for (size_t i = 0; i < size; ++i)
	{
		cells[i] = _cells[i];
	}
}

template<typename T>
Column<T>::Column(const char* type): size(0), title(""), cells(nullptr)
{
	setType(type);
}

template<typename T>
Column<T>::Column() : size(0), title(""), type(""), cells(nullptr)
{
}

template<typename T>
Column<T>::~Column()
{
	delete[] cells;
}

//връща броя на цифрите в клетката
template<typename T>
size_t Column<T>::getCellLength(size_t ind) const
{
	if (cells[ind] == NULL) return 4;
	return digits(cells[ind]);
}

//връща броя на символите в клетката
template<>
inline size_t Column<std::string>::getCellLength(size_t ind) const
{
	return cells[ind].size();
}

template<typename T>
std::ostream& Column<T>::printCellLine(std::ostream& out) const
{
	size_t length = getLongest() + 6;
	out << "+";
	printMany("-", length, out);
	return out;
}

template<typename T>
std::ostream& Column<T>::printCellTitle(std::ostream& out) const
{
	size_t length = getLongest() + 6;
	size_t pad = length - title.size();
	out << "|";

	printPadding(title.size(), pad, out);

	out << title;

	printPadding(title.size(), pad, out);
	return out;
}

template<typename T>
std::ostream& Column<T>::printCellInsides(size_t i, std::ostream& out) const 
{
	size_t length = getLongest() + 6; //to do longest with null

	if (cells[i] == NULL) {
		size_t pad = length - 4;
		out << "|";

		printPadding(4, pad, out);

		out << "NULL";

		if (isOdd(pad))pad = pad - 1;
		printPadding(4, pad, out);
	}
	else {
		size_t pad = length - getCellLength(i);

		out << "|";

		printPadding(getCellLength(i), pad, out);

		out << cells[i];

		if (isOdd(pad))pad = pad - 1;
		printPadding(getCellLength(i), pad, out);
	}

	return out;
}

template<>
inline std::ostream& Column<std::string>::printCellInsides(size_t i, std::ostream & out) const
{
	size_t length = getLongest() + 6;
	size_t pad = length - getCellLength(i);

	out << "|";

	printPadding(getCellLength(i), pad, out);

	out << cells[i];

	if (isOdd(pad))pad = pad - 1;
	printPadding(getCellLength(i), pad, out);

	return out;
}

template<typename T>
std::ostream& Column<T>::printPadding(size_t length, size_t pad, std::ostream& out) const
{
	if (isOdd(length)) {
		printMany(" ", (pad + 1) / 2, out);
	}
	else printMany(" ", pad / 2, out);
	return out;
}

template<typename T>
size_t Column<T>::getColSize() const
{
	return size;
}

template<typename T>
inline std::string Column<T>::getType() const
{
	return type;
}

template<typename T>
inline std::string Column<T>::getTitle() const
{
	return title;
}

template<typename T>
std::string Column<T>::getCellAt(size_t ind) const
{
	if (cells[ind] == NULL) return "NULL";
	return std::to_string(cells[ind]);
}

template<>
inline std::string Column<std::string>::getCellAt(size_t ind) const
{
	return cells[ind];
}

template<typename T>
void Column<T>::addCell(std::string cell)
{
	T* temp = new T[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = cells[i];
	}
	delete[] cells;

	cells = new T[++size];
	for (size_t i = 0; i < size - 1; ++i)
	{
		cells[i] = temp[i];
	}
	cells[size - 1] = cell;
}

template<>
inline void Column<int>::addCell(std::string cell)
{
	int* temp = new int[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = cells[i];
	}
	delete[] cells;

	cells = new int[++size];
	for (size_t i = 0; i < size - 1; ++i)
	{
		cells[i] = temp[i];
	}
	cells[size - 1] = std::stoi(cell);
}

template<>
inline void Column<double>::addCell(std::string cell)
{
	double* temp = new double[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = cells[i];
	}
	delete[] cells;

	cells = new double[++size];
	for (size_t i = 0; i < size - 1; ++i)
	{
		cells[i] = temp[i];
	}
	cells[size - 1] = std::stod(cell);
}
//template<typename T>
//void Column<T>::addCell(std::string cell)
//{
//	if (type == "string") {
//
//		T* temp = new T[size];
//		for (size_t i = 0; i < size; ++i)
//		{
//			temp[i] = cells[i];
//		}
//		delete[] cells;
//
//		cells = new T[++size];
//		for (size_t i = 0; i < size - 1; ++i)
//		{
//			cells[i] = temp[i];
//		}
//		cells[size - 1] = cell;
//	}
//	if (type == "double") {
//		T* temp = new T[size];
//		for (size_t i = 0; i < size; ++i)
//		{
//			temp[i] = cells[i];
//		}
//		delete[] cells;
//
//		cells = new T[++size];
//		for (size_t i = 0; i < size - 1; ++i)
//		{
//			cells[i] = temp[i];
//		}
//		cells[size - 1] = std::stod(cell);
//	}
//	if (type == "int") {
//		T* temp = new T[size];
//		for (size_t i = 0; i < size; ++i)
//		{
//			temp[i] = cells[i];
//		}
//		delete[] cells;
//
//		cells = new T[++size];
//		for (size_t i = 0; i < size - 1; ++i)
//		{
//			cells[i] = temp[i];
//		}
//		cells[size - 1] = std::stoi(cell);
//	}
//
//
//}


//template<typename T>
//void Column<T>::setNullCell(size_t ind)
//{
//	cells[ind] = NULL;
//}

template<typename T>
void Column<T>::setTitle(std::string t)
{
	title = t;
}

template<typename T>
void Column<T>::setType(const char* t)
{
	assert(strcmp(t, "int") || strcmp(t, "string") || strcmp(t, "double"));
	type = t;
}

//връща дължината на най-дългата клетка
template<typename T>
size_t Column<T>::getLongest() const
{
	int max = 0;
	for (size_t i = 1; i < size; ++i)
	{
		if (getCellLength(max) < getCellLength(i)) {
			max = i;
		}
	}
	if (title.size() > getCellLength(max)) {
		return title.size();
	}
	return getCellLength(max);
}

template<typename T>
void Column<T>::printCell(size_t ind) const
{
	std::cout << cells[ind];
}

template<typename T>
void Column<T>::print() const
{
	printCellLine(std::cout);
	std::cout << "+\n";
	printCellTitle(std::cout);
	std::cout << "|\n";

	printCellLine(std::cout);
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "+\n";
		printCellInsides(i, std::cout);
		std::cout << "|\n";
		printCellLine(std::cout);
	}
	std::cout << "+";
	std::cout << "\n";
}

//извежда на екрана даден символ по даден брой пъти един след друг
template<typename T>
std::ostream& Column<T>::printMany(const char* ch, size_t n, std::ostream& out) const
{
	for (size_t i = 0; i < n; ++i)
	{
		out << ch;
	}
	return out;
}

template<typename T>
int Column<T>::digits(int n) const
{
	if (n == 0)	return 0;
	return 1 + digits(n / 10);
}

template<typename T>
bool Column<T>::isOdd(int n) const
{
	return n % 2 != 0;
}

template<typename T>
void Column<T>::setNullCellAt(size_t ind)
{
	cells[ind] = NULL;
}

template<>
inline void Column<std::string>::setNullCellAt(size_t ind)
{
	assert(ind < size);
	cells[ind] = "NULL";
}
