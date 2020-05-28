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

//конструктор по подразбиране
Table::Table(): cols(nullptr), size(0), name("")
{
}

//конструктор с параметри
Table::Table(IColumn** arr, size_t s, const std::string& n) : name(n), cols(nullptr), size(0)
{
	setCol(arr, s);
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
	size_t max = getMaxColSize();

	for (size_t i = 0; i < max; ++i)
	{
		printTableLine(out);
		for (size_t j = 0; j < size; ++j)
		{
			if (cols[j]->getColSize() < i + 1)	cols[j]->printCellContents(-1, out);
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

	delete[] temp;
	return in;
}

std::ostream& Table::write(std::ostream& out) const
{
	out << "Table name: " << name << std::endl
		<< "Columns: " << size << std::endl
		<< "Rows: " << getMaxColSize() << std::endl
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

//връща големината на най-голямата колона 
size_t Table::getMaxColSize() const
{
	size_t max = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (max < cols[i]->getColSize()) max = cols[i]->getColSize();
	}
	size_t colSize = max;
	return max;
}
