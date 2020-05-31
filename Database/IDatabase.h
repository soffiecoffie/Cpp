#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>

/** @brief клас IDatabase е интерфейсен клас на Database */
class IDatabase
{
public:
	/** @brief деструктор */
	virtual ~IDatabase() = 0 {};

	virtual void open(std::string) = 0;
	virtual void close() = 0;
	virtual void save() = 0;
	virtual void saveas(std::string) = 0;
	virtual void exit() = 0;
	virtual void help();

	virtual bool getIsDone() const = 0;
	virtual bool getIsOpen() const = 0;
	virtual bool getIsPageCmdOn() const = 0;

	virtual void out() = 0;
	virtual void next(std::string) = 0;
	virtual void previous(std::string) = 0;
	virtual void print(std::string) = 0;

	virtual void import(std::string) = 0;
	virtual void showtables() const = 0;
	virtual void describe(std::string) const = 0;
	virtual void myExport(std::string, std::string) const = 0;
	virtual void rename(std::string, std::string) = 0;
	virtual void addColumn(std::string, std::string, std::string) = 0;

};

#endif