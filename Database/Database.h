#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"
#include "IDatabase.h"
#include "Invoker.h"
#include <vector>
#include <string>
#include <fstream>

/** @brief клас Database създава база от данни */
class Database: public IDatabase
{
	std::vector<ITable*> tables;		//таблиците които са отворени ако има такива
	std::string catalog = "";			//името на каталога на базата от данни
	std::vector<std::string> tableInfo; 

private:
	void del();
	bool isImported(std::string) const;

	bool isDone = 0;
	bool isOpen = 0;
	bool isPageCmdOn = 0;

	size_t start = 0, end = 0;

public:
	Database();
	Database(const Database&) = delete;
	Database(std::vector<ITable*>, std::string, std::vector<std::string>);
	~Database();

	void setCatalogName(std::string);

	void open(std::string);
	void close();
	void save();
	void saveas(std::string);
	void exit();

	void import(std::string); 
	void showtables() const;
	void describe(std::string) const;
	void myExport(std::string, std::string) const;
	void print(std::string);
	void rename(std::string, std::string);
	
	void out();
	void next(std::string);
	void previous(std::string);


	void addColumn(std::string, std::string, std::string);

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;

	ITable* getTableByName(std::string) const;
	
	bool getIsOpen() const;
	bool getIsDone() const;
	bool getIsPageCmdOn() const;
};


#endif