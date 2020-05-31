#ifndef ICOLUMN__H
#define ICOLUMN__H
#include <string>

class IColumn
{

public:
	virtual ~IColumn() = 0 {};
	virtual void addCell(std::string) = 0;

	virtual std::ostream& printCellLine(std::ostream&) const = 0;
	virtual std::ostream& printCellTitle(std::ostream&) const = 0;
	virtual std::ostream& printCellContents(size_t, std::ostream&) const = 0;

	virtual size_t getRowSize() const = 0;
	virtual std::string getType() const = 0;
	virtual std::string getTitle() const = 0;

	virtual std::string getCellAt(size_t) const = 0;

	virtual void setNullCellAt(size_t) = 0;

	virtual void setType(const std::string&) = 0;
	virtual void setTitle(const std::string&) = 0;
	virtual void copyOtherCells(const IColumn&) = 0;
	virtual void print() const = 0;

	IColumn& operator=(const IColumn&);
	//Или направи няколко функции които приемат разл неща
	//или направи темплейтна темплейтна функция
	//virtual void addCell(double) = 0;
	//virtual void addCell(std::string) = 0;
	//virtual std::string removePaddingFromStr(std::string s);

};

#endif
