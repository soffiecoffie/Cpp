/*
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
void Column<T>::printMany(const char* ch, int n) const
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
		pad = length - 3 - getCellLength(i);

		std::cout << "\n|";
		printMany(" ", pad);

		std::cout << cells[i];

		if (isOdd(pad)) {
			printMany(" ", pad - 1);
		}
		else printMany(" ", pad);

		std::cout << "|\n";
	}
}

template<typename T>
void Column<T>::print() const
{
	int length = getLongest();
	length += 6; //по 3 " " минимум от всяка страна
	for (size_t i = 0; i < length; ++i)
	{
		std::cout << "-";
	}

	int pad = length - 3 - title.size();
	std::cout << "\n|";
	printMany(" ", pad);
	std::cout << title;
	if (isOdd(pad)) {
		printMany(" ", pad - 1);
	}
	else printMany(" ", pad);
	std::cout<<"|\n";

	printCellContents(length);
}

int digits(int n, int count)
{
	if (n / 10 == 0) return ++count;
	n /= 10;
	++count;
	return digits(n, count);
}

bool isOdd(int n)
{
	return n % 2 == 0;
}

*/