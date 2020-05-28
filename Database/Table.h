#ifndef TABLE_H
#define TABLE_H

//#include "IColumn.h"
#include "Column.h"
#include <string>

class Table
{
	size_t size;
	IColumn** cols;
	std::string name;

private:
	void del();

public:
	Table();
	Table(IColumn**, size_t, const std::string&);
	~Table();

	std::ostream& print(std::ostream& out) const;
	std::ostream& printTableLine(std::ostream& out) const;
	std::ostream& printTableTitles(std::ostream& out) const;
	std::ostream& printTableRow(std::ostream& out) const;

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;
	
	std::string removePaddingFromStr(std::string s);

	void setCol(IColumn* [], size_t);

	size_t getMaxColSize() const;

};

#endif
