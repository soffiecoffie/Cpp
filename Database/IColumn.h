#ifndef ICOLUMN__H
#define ICOLUMN__H
#include <string>

class IColumn
{

public:
	virtual void addCell(std::string) = 0;

	virtual std::ostream& printCellLine(std::ostream&) const = 0;
	virtual std::ostream& printCellTitle(std::ostream&) const = 0;
	virtual std::ostream& printCellInsides(size_t, std::ostream&) const = 0;

	virtual size_t getColSize() const = 0;
	virtual std::string getType() const = 0;
	virtual std::string getTitle() const = 0;
	virtual void printCell(size_t) const = 0;

	virtual std::string getCellAt(size_t) const = 0;

	virtual void setNullCellAt(size_t) = 0;

	virtual void setType(const char*) = 0;
	virtual void setTitle(std::string) = 0;
	
};

#endif
