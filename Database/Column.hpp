#include "Column.h"
#include <iomanip>
#include <iostream>

template<typename T>
Column<T>::Column(const char* _title, const T* _cells, size_t _size) : size(_size), cells(new T[_size])
{
	title = _title;

	for (size_t i = 0; i < size; ++i)
	{
		cells[i] = _cells[i];
	}
}

//template<typename T>
//Column<T>::Column(const std::string& _title, const T* _cells, size_t _size) : size(_size), cells(new T[_size])
//{
//	title = _title;
//
//	for (size_t i = 0; i < size; ++i)
//	{
//		cells[i] = _cells[i];
//	}
//}

template<typename T>
Column<T>::Column() : size(0), title(""), cells(nullptr)
{
}

template<typename T>
Column<T>::~Column()
{
	delete[] cells;
}

template<typename T>
inline void Column<T>::printCellLine() const
{
	size_t length = getLongest() + 6;
	std::cout << "+";
	printMany("-", length);
}

template<typename T>
inline void Column<T>::printCellTitle() const
{
	size_t length = getLongest() + 6;
	size_t pad = length - title.size();
	std::cout << "|";

	printPadding(title.size(), pad);

	std::cout << title;

	printPadding(title.size(), pad);
}

template<typename T>
void Column<T>::printCellInsides(size_t i) const
{
	size_t length = getLongest() + 6;
	size_t pad = length - getCellLength(i);

	std::cout << "|";

	printPadding(getCellLength(i), pad);
	
	std::cout << cells[i];

	if (isOdd(pad))pad = pad - 1;
	printPadding(getCellLength(i), pad);
}

template<typename T>
void Column<T>::printCell() const
{
	size_t length = getLongest() + 6;
	std::cout << "\n";
	print();
}

template<typename T>
void Column<T>::printPadding(size_t length, size_t pad) const
{
	if (isOdd(length)) {
		printMany(" ", (pad + 1) / 2);
	}
	else printMany(" ", pad / 2);
}

template<typename T>
size_t Column<T>::getColSize() const
{
	return size;
}


//template<typename T>
//void Column<T>::setNullCell(size_t ind)
//{
//	cells[ind] = NULL;
//}

//template<typename U>
//void printCentered(const U)
//{
//}
//
//template<>
//void printCentered(const char*)
//{
//}

//template<typename T>
//void Column<T>::printCentered(T ch) const
//{
//	int pad = length - 3 - getCellLength(i);
//
//	std::cout << "\n|";
//	printMany(" ", pad);
//
//	std::cout << ch;
//
//	if (isOdd(pad)) {
//		printMany(" ", pad - 1);
//	}
//	else printMany(" ", pad);
//
//	std::cout << "|\n";
//}
//
//template<typename T>
//void Column<T>::printCentered(const std::string& ch) const
//{
//	int pad = length - 3 - ch.size();
//
//	std::cout << "\n|";
//	printMany(" ", pad);
//
//	std::cout << ch;
//
//	if (isOdd(pad)) {
//		printMany(" ", pad - 1);
//	}
//	else printMany(" ", pad);
//
//	std::cout << "|\n";
//}

template<typename T>
inline void Column<T>::addCell(T cell)
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
		temp[i] = cells[i];
	}
	cells[size - 1] = cell;
}

template<typename T>
inline void Column<T>::setTitle(const char* t)
{
	title = t;
}

//връща броя на цифрите в клетката
template<typename T>
size_t Column<T>::getCellLength(size_t ind) const
{
	return digits(cells[ind]);
}

//връща броя на символите в клетката
template<>
size_t Column<std::string>::getCellLength(size_t ind) const
{
	return cells[ind].size();
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

//извежда на екрана даден символ по даден брой пъти един след друг
template<typename T>
void Column<T>::printMany(const char* ch, size_t n) const
{
	for (size_t i = 0; i < n; ++i)
	{
		std::cout << ch;
	}
}

template<typename T>
void Column<T>::printCellContents(size_t length) const
{
	int pad;

	for (size_t i = 0; i < size; ++i)
	{
		pad = length - getCellLength(i);

		std::cout << "\n|";
		if (isOdd(getCellLength(i))) {
			printMany(" ", (pad + 1) / 2);
		}
		else printMany(" ", pad / 2);

		std::cout << cells[i];

		if (isOdd(getCellLength(i))) {
			printMany(" ", (pad+1)/2-1);
		}
		else printMany(" ", pad/2);

		std::cout << "|\n";
		
		std::cout << "+";
		printMany("-", length);
		std::cout << "+";

		//std::cout << "|";
		//printMany("-", length );
		//std::cout << "|";

	}
}

template<typename T>
void Column<T>::print() const
{
	int length = getLongest();
	length += 6; //по 3 " " минимум от всяка страна
	//printMany("-", length + 2);
	std::cout << "+";
	printMany("-", length);
	std::cout << "+";


	int pad = length - title.size();
	std::cout << "\n|";

	if (isOdd(title.size())) {
		printMany(" ", (pad + 1) / 2);
	}
	else printMany(" ", pad / 2);

	std::cout << title;

	if (isOdd(title.size())) {
		printMany(" ", (pad + 1) / 2 - 1);
	}
	else printMany(" ", pad / 2);

	std::cout << "|\n";

	std::cout << "+";
	printMany("-", length);
	std::cout << "+";
	
	//std::cout << "|";
	//printMany("-", length);
	//std::cout << "|";
	
	//printMany("-", length+2);

	printCellContents(length);
}

int digits(int n)
{
	if (n == 0)	return 0;
	return 1 + digits(n / 10);
}

bool isOdd(int n)
{
	return n % 2 != 0;
}
