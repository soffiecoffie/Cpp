#include "Table.h"
#include "Utils.h"
#include <iostream>
#include <cassert>

//изтрива динамичната памет
void Table::del()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete cols[i];
	}
	delete[] cols;
}

//добавя още 1 място за колона таблицата
void Table::addSpace()
{
	IColumn* temp[240];
	for (size_t i = 0; i < size; ++i)
	{
		if (cols[i]->getType() == "int") {
			temp[i] = new Column<int>("int");
		}
		else if (cols[i]->getType() == "string") {
			temp[i] = new Column<std::string>("string");
		}
		else if (cols[i]->getType() == "double") {
			temp[i] = new Column<double>("double");
		}

		*temp[i] = *cols[i];
	}

	del();

	cols = new IColumn * [++size];
	for (size_t i = 0; i < size - 1; ++i)
	{
		if (temp[i]->getType() == "int") {
			cols[i] = new Column<int>("int");
		}
		else if (temp[i]->getType() == "string") {
			cols[i] = new Column<std::string>("string");
		}
		else if (temp[i]->getType() == "double") {
			cols[i] = new Column<double>("double");
		}

		*cols[i] = *temp[i];
	}

	for (size_t i = 0; i < size - 1; ++i)
	{
		delete temp[i];
	}
}

//конструктор по подразбиране
Table::Table(): cols(nullptr), size(0), name("")
{
}

//копи конструктор
Table::Table(const Table& other) : Table(other.getCols(), other.getSize(), other.getName(), other.getFileName())
{
}

//конструктор с параметри
Table::Table(IColumn** arr, size_t s, const std::string& n) : name(n), cols(nullptr), size(0)
{
	setCol(arr, s);
}

//конструктор с параметри
Table::Table(IColumn** arr, size_t s, const std::string& n, const std::string& fname) : Table(arr, s, n)
{
	setFileName(fname);
}

//деструктор
Table::~Table()
{
	del();
}

//принтира таблицата
std::ostream& Table::print(std::ostream& out) const
{
	printTableLine(out);

	printTableTitles(out);

	printTableRow(out);

	printTableLine(out);

	return out;
}

//принтира линията на таблицата
std::ostream& Table::printTableLine(std::ostream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellLine(out);
	}
	out << "+\n";
	return out;
}

//принтира заглавията
std::ostream& Table::printTableTitles(std::ostream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellTitle(out);
	}
	
	out << "|\n";
	return out;
}

//принтира редовете
std::ostream& Table::printTableRow(std::ostream& out) const
{
	size_t max = getMaxRowSize();

	for (size_t i = 0; i < max; ++i)
	{
		printTableLine(out);
		for (size_t j = 0; j < size; ++j)
		{
			if (cols[j]->getRowSize() < i + 1)	cols[j]->printCellContents(-1, out);
			else cols[j]->printCellContents(i, out);
		}
		out << "|\n";
	}
	return out;
}

std::istream& Table::read(std::istream& in)
{
	in.ignore(12);
	getline(in, name);
	
	in.ignore(9);
	in >> size;

	size_t rows;
	in.ignore(6);
	in >> rows;

	cols = new IColumn * [size];

	in.ignore(1,'\n');
	in.ignore(14);

	char* temp = new char[100];
	for (size_t i = 0; i < size; ++i)
	{
		if (i == size - 1) in.getline(temp, 64, ' ');
		else in.getline(temp, 64, ',');
		in.ignore(1);
		if (strcmp(temp, "int") == 0) {
			cols[i] = new Column<int>("int");
		}
		else if (strcmp(temp, "string") == 0) {
			cols[i] = new Column<std::string>("string");
		}
		else if (strcmp(temp, "double") == 0) {
			cols[i] = new Column<double>("double");
		}
		//cols[i]->setType(temp);
	}
	in.ignore(2, '\n\n');
	in.ignore(256, '\n');

	for (size_t i = 0; i < size; ++i)
	{
		in.ignore(1);
		in.getline(temp, 64, '|');
		cols[i]->setTitle(removePaddingFromStr(temp));
	}
	in.ignore(1);

	for (size_t i = 0; i < rows - 1; ++i) 
	{
		in.ignore(256, '\n'); //игнорира линията
		for (size_t j = 0; j < size; ++j)
		{
			in.ignore(1);
			in.getline(temp, 64, '|');
			cols[j]->addCell(removePaddingFromStr(temp)); //премахва празното място около съдържанието на клетката и я добавя
		}
		in.ignore(2, '\n');
	}

	delete[] temp;
	return in;
}

std::ostream& Table::write(std::ostream& out) const
{
	out << "Table name: " << name << std::endl
		<< "Columns: " << size << std::endl
		<< "Rows: " << getMaxRowSize() + 1 << std::endl
		<< "Column types: ";

	for (size_t i = 0; i < size; ++i)
	{
		out << cols[i]->getType();
		if (i == size - 1) 
			out << " ";
		else out << ", ";

		/*in.getline(temp, 256, '\n');
		std::cout << temp;*/
	}
	out << std::endl << std::endl;
	print(out);

	return out;
}

//връща копие на подадената дума без допълнителното място около нея
std::string Table::removePaddingFromStr(std::string s)
{
	std::string result = s;
	size_t ind = 0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (s[i] != ' ') {
			result[ind++] = s[i];
		}
		else if (isSpaceBetweenWords(s, i)) {
			result[ind++] = s[i];
		}
	}
	result.resize(ind);

	return result;
}

void Table::printFromTo(size_t start, size_t end) const
{

	printTableLine(std::cout);

	printTableTitles(std::cout);

	printRows(start, end);

	printTableLine(std::cout);

}

void Table::printRows(size_t start, size_t end) const
{
	for (size_t i = start; i < end; ++i)
	{
		printTableLine(std::cout);
		for (size_t j = 0; j < size; ++j)
		{
			if (cols[j]->getRowSize() < i + 1)	cols[j]->printCellContents(-1, std::cout);
			else cols[j]->printCellContents(i, std::cout);
		}
		std::cout << "|\n";
	}
}

//задава стойности на колоните
void Table::setCol(IColumn* arr[], size_t s)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete cols[i];
	}
	delete[] cols;

	size = s;
	cols = new IColumn * [s];

	for (size_t i = 0; i < size; ++i)
	{
		int j = 0;
		if (arr[i]->getType() == "string") {
			cols[i] = new Column<std::string>;
		}
		else if (arr[i]->getType() == "double") {
			cols[i] = new Column<double>;
		}
		else {
			cols[i] = new Column<int>;
		}
		cols[i] = arr[i];
	}

}

//задава нова стойност на името на файла
void Table::setFileName(const std::string& str)
{
	filename = str;
}

void Table::setName(const std::string& newName)
{
	name = newName;
}

//добавя нова колона
void Table::addCol(std::string colName, std::string type)
{
	addSpace();

	--size;
	if (type == "int") {
		cols[size ] = new Column<int>("int", colName, getMaxRowSize());
	}
	else if (type == "string") {
		cols[size ] = new Column<std::string>("string", colName, getMaxRowSize());
	}
	else if (type == "double") {
		cols[size ] = new Column<double>("double", colName, getMaxRowSize());
	}
	++size;
	//cols[size-1]->print();
}

//връща големината на най-голямата колона 
size_t Table::getMaxRowSize() const
{
	size_t max = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (max < cols[i]->getRowSize()) max = cols[i]->getRowSize();
	}
	size_t colSize = max;
	return max;
}

//връща броя на колоните
size_t Table::getSize() const
{
	return size;
}

//връща името на файла, в който е записан
std::string Table::getFileName() const
{
	return filename;
}

//връща името на таблицата
std::string Table::getName() const
{
	return name;
}

//връща масива от указатели към колони на таблицата
IColumn** Table::getCols() const
{
	return cols;
}

IColumn* Table::getColumnByName(std::string name) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (cols[i]->getTitle() == name) return cols[i];
	}
	return nullptr;
}


/*

#include "Table.h"
#include <iostream>
#include <cassert>


Table::Table(): cols(nullptr), size(0), name("")
{
}

Table::Table(IColumn* arr[], size_t s, const std::string& n) : size(s), name(n)
{
	cols = new IColumn*[s];
	for (size_t i = 0; i < size; ++i)
	{
		cols[i] = arr[i];
	}
}

Table::~Table()
{
	//for (size_t i = 0; i < size; ++i)
	//{
	//	delete cols[i];
	//}
	delete[] cols;
}

//void Table::print() const
//{
//	printTableLine();
//
//	printTableTitles();
//
//	printTableRow();
//
//	printTableLine();
//}
//
//void Table::printTableLine() const
//{
//	for (size_t i = 0; i < size; ++i)
//	{
//		cols[i]->printCellLine();
//	}
//	std::cout << "+\n";
//}
//
//void Table::printTableTitles() const
//{
//	for (size_t i = 0; i < size; ++i)
//	{
//		cols[i]->printCellTitle();
//	}
//	std::cout << "|\n";
//}
//
//void Table::printTableRow() const
//{
//	size_t max = 0;
//	for (size_t i = 0; i < size; ++i)
//	{
//		if (max < cols[i]->getRowSize()) max = cols[i]->getRowSize();
//	}
//	size_t colSize = max;
//
//	//if one col is shorter then make cells say NULL		TODO
//	for (size_t i = 0; i < max; ++i)
//	{
//		printTableLine();
//		for (size_t j = 0; j < size; ++j)
//		{
//			cols[j]->printCellContents(i);
//		}
//		std::cout << "|\n";
//	}
//}
//

std::ostream& Table::print(std::ostream& out) const
{
	printTableLine(out);

	printTableTitles(out);

	printTableRow(out);

	printTableLine(out);

	return out;
}

std::ostream& Table::printTableLine(std::ostream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellLine(out);
	}
	out << "+\n";
	return out;
}

std::ostream& Table::printTableTitles(std::ostream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		cols[i]->printCellTitle(out);
	}

	out << "|\n";
	return out;
}

std::ostream& Table::printTableRow(std::ostream& out) const
{
	size_t max = getMaxRowSize();

	//if one col is shorter then make cells say NULL		TODO
	for (size_t i = 0; i < max; ++i)
	{
		printTableLine(out);
		for (size_t j = 0; j < size; ++j)
		{
			cols[j]->printCellContents(i, out);
		}
		out << "|\n";
	}
	return out;
}

std::istream& Table::read(std::istream& in)
{
	in.ignore(12);
	getline(in, name);

	in.ignore(9);
	in >> size;

	size_t rows;
	in.ignore(6);
	in >> rows;

	cols = new IColumn * [size];

	in.ignore(1,'\n');
	in.ignore(14);

	//IColumn* ptr=&Column<int>();
	char* temp = new char[10];
	for (size_t i = 0; i < size; ++i)
	{
		in.getline(temp, 64, ' ');
		if (strcmp(temp, "int") == 0) {
			cols[i] = new Column<int>("int");
		}
		if (strcmp(temp, "string") == 0) {
			cols[i] = new Column<std::string>("string");
		}
		if (strcmp(temp, "double") == 0) {
			cols[i] = new Column<double>("double");
		}
		cols[i]->setType(temp);
	}
	in.ignore(2, '\n\n');
	in.ignore(256, '\n');

	for (size_t i = 0; i < size; ++i)
	{
		in.ignore(1);
		in.getline(temp, 64, '|');//""?
		cols[i]->setTitle(removePaddingFromStr(temp));
	}
	in.ignore(1);

	for (size_t i = 0; i < rows - 1; ++i) //i< max col size //write add col size
	{
		in.ignore(256, '\n'); //ignore line
		for (size_t j = 0; j < size; ++j)
		{
			in.ignore(1);
			in.getline(temp, 64, '|');//""?
			cols[j]->addCell(removePaddingFromStr(temp)); //TODO
		}
		in.ignore(2, '\n');
	}

	return in;
}

std::ostream& Table::write(std::ostream& out) const
{
	out << "Table name: " << name << std::endl
		<< "Columns: " << size << std::endl
		<< "Rows: " << getMaxRowSize() << std::endl
		<< "Column types: ";

	for (size_t i = 0; i < size; ++i)
	{
		out << cols[i]->getType();
		out << " ";
	}
	out << std::endl << std::endl;
	print(out);

	return out;
}

////връща копие на подадената дума без допълнителното място около нея
//std::string Table::removePaddingFromStr(std::string s)
//{
//	std::string result = s;
////	char* result = new char[s.size()];
//	size_t ind = 0;
//	for (size_t i = 0; i < s.size(); ++i)
//	{
////		if (s[i] == ' ' && !isSpaceBetweenWords(s, i)) {
////			result.erase(result.begin() + i, result.begin() + i +1);
////		}
//		if (s[i] != ' ') {
//			result[ind++] = s[i];
//			//result[ind] = '\0';
//		}
//		else if (isSpaceBetweenWords(s, i)) {
//			result[ind++] = s[i];
//		}
//	}
//	char* helper = new char[ind];
//	for (size_t i = 0; i < ind; ++i)
//	{
//		helper[i] = result[i];
//	}
//	helper[ind] = '\0';
//
//	result = helper;
//	//	result.erase(ind, result.size());
////	res = result;
////	result.erase(result.begin()+ind, result.end());
//	return result;
//}

//връща копие на подадената дума без допълнителното място около нея
std::string Table::removePaddingFromStr(std::string s)
{
	std::string result = s;
	size_t ind = 0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		//		if (s[i] == ' ' && !isSpaceBetweenWords(s, i)) {
		//			result.erase(result.begin() + i, result.begin() + i +1);
		//		}
		if (s[i] != ' ') {
			result[ind++] = s[i];
		}
		else if (isSpaceBetweenWords(s, i)) {
			result[ind++] = s[i];
		}
	}
	result.resize(ind);

	return result;
}

//проверява дали празното място на подадения индекс в дадения низ се намира между думи
bool Table::isSpaceBetweenWords(std::string str, size_t ind)
{
	assert(str[ind] == ' ');
	if (ind != str.size() - 1 && ind != 0) {
		return (str[ind - 1] != ' ') && (str[ind + 1] != ' ');
	}
	return false; //ако е първия или последния символ
}

size_t Table::getMaxRowSize() const
{
	size_t max = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (max < cols[i]->getRowSize()) max = cols[i]->getRowSize();
	}
	size_t colSize = max;
	return max;
}



*/