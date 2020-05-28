#include <iomanip>
#include <iostream>
#include <cassert>
#include "Column.h"
#include "Utils.h"

//конструктор с параметри
template<typename T>
Column<T>::Column(const std::string& _title, const std::string& _type, const T* _cells, size_t _size)
				 : size(0), cells(nullptr), title(_title)
{
	setType(_type);
	setCells(_cells, _size);
}

//конструктор с параметър
template<typename T>
Column<T>::Column(const char* type): size(0), title(""), cells(nullptr)
{
	setType(type);
}

//конструктор по подразбиране
template<typename T>
Column<T>::Column() : size(0), title(""), type(""), cells(nullptr)
{
}

//деструктор
template<typename T>
Column<T>::~Column()
{
	del();
}

//изтрива динамичната памет
template<typename T>
void Column<T>::del()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete cells[i];
	}
	delete[] cells;
}

//добавя още едно място към масива
template<typename T>
void Column<T>::addSpace()
{
	T* temp = new T[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = *cells[i];
	}

	del();

	cells = new T * [++size];
	for (size_t i = 0; i < size - 1; ++i)
	{
		cells[i] = new T;
		*cells[i] = temp[i];
	}

	delete[] temp;
}

//връща броя на цифрите в клетката
template<typename T>
size_t Column<T>::getCellLength(size_t ind) const
{
	if (cells[ind] == nullptr) return 4;
	return digits(*cells[ind]);
}

//връща броя на символите в клетката
template<>
inline size_t Column<std::string>::getCellLength(size_t ind) const
{
	if (cells[ind] == nullptr) return 4;
	return cells[ind]->size();
}

//принтира линията на клетката
template<typename T>
std::ostream& Column<T>::printCellLine(std::ostream& out) const
{
	size_t length = getLongest() + 6;
	out << "+";
	printMany("-", length, out);
	return out;
}

//принтира заглавието на клетката
template<typename T>
std::ostream& Column<T>::printCellTitle(std::ostream& out) const
{
	size_t length = getLongest() + 6;
	size_t pad = length - title.size();
	out << "|";
	
	if (isOdd(pad)) printPadding(pad + 1, out);
	else printPadding(pad, out);

	out << title;

	printPadding(pad, out);
	return out;
}

//принтира съдържанието на клетката
template<typename T>
std::ostream& Column<T>::printCellContents(size_t i, std::ostream& out) const 
{
	size_t pad, length = getLongest() + 6;		//+6 е за празното място около съдържанието на клетката (мин. 3 " " от двете страни)

	if (cells[i] == nullptr || i == -1) {		
		pad = length - 4;
		out << "|";

		if (isOdd(pad)) printPadding(pad + 1, out); 
		else printPadding(pad, out);

		out << "NULL";
	}
	else {
		pad = length - getCellLength(i);

		out << "|";

		if (isOdd(pad)) printPadding(pad + 1, out); 
		else printPadding(pad, out);

		out << *cells[i];
	}

	printPadding(pad, out);
	
	return out;
}

//принтира празно място
template<typename T>
std::ostream& Column<T>::printPadding(size_t pad, std::ostream& out) const
{
	printMany(" ", pad / 2, out);
	return out;
}

//връща големината на колоната
template<typename T>
size_t Column<T>::getColSize() const
{
	return size;
}

//връща низ с типа на колоната
template<typename T>
std::string Column<T>::getType() const
{
	return type;
}

//връща заглавието на колоната
template<typename T>
std::string Column<T>::getTitle() const
{
	return title;
}

//връща низ от стойността на дадена клетка
template<typename T>
std::string Column<T>::getCellAt(size_t ind) const
{
	if (cells[ind] == nullptr) return "NULL";
	return std::to_string(*cells[ind]);
}

//връща низ от стойността на дадена клетка на колона от тип std::string
template<>
inline std::string Column<std::string>::getCellAt(size_t ind) const
{
	return *cells[ind];
}

//връща масив от указатели към стойностите на колоната
template<typename T>
T** Column<T>::getCells() const
{
	return cells;
}

//добавя нова клетка
template<typename T>
void Column<T>::addCell(std::string cell)
{
	addSpace();

	cells[size - 1] = new T(cell);
}

//добавя нова клетка в колона от тип int
template<>
inline void Column<int>::addCell(std::string cell)
{
	addSpace();

	cells[size - 1] = new int(std::stoi(cell)); 
}

//добавя нова клетка в колона от тип double
template<>
inline void Column<double>::addCell(std::string cell)
{
	addSpace();

	cells[size - 1] = new double(std::stod(cell));
}

//задава стойност на заглавието
template<typename T>
void Column<T>::setTitle(const std::string& t)
{
	title = t;
}

//задава стойност на масива от указатели
template<typename T>
void Column<T>::setCells(const T* arr, size_t s)
{
	del();

	size = s;
	
	cells = new T* [s];
	for (size_t i = 0; i < s; ++i)
	{
		cells[i] = new T(arr[i]);
	}
}

//задава стойност на типа на колоната
template<typename T>
void Column<T>::setType(const std::string& t)
{
	assert(t == "int" || t == "string" || t == "double");
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

//принтира колоната
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
		printCellContents(i, std::cout);
		std::cout << "|\n";
		printCellLine(std::cout);
	}
	std::cout << "+";
	std::cout << "\n";
}

//задава стойността на дадена клетка да бъде nullptr
template<typename T>
void Column<T>::setNullCellAt(size_t ind)
{
	cells[ind] = nullptr;
}
