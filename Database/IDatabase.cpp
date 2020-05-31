#include "IDatabase.h"
#include <iostream>

void IDatabase::help()
{
	std::cout << "\nThe following commands are supported: \n\n"
		<< "> open <file> - opens <file>\n"
		<< "> close - closes currently opened file\n"
		<< "> save - saves the currently open file\n"
		<< "> saveas <file> - saves the currently opened file in <file>\n"
		<< "> help - prints this information\n"
		<< "> exit - exits the program\n"
		<< "> import <file name> - adds a new table to the database\n"
		<< "> showtables - prints a list of all the tables in the database\n"
		<< "> describe <name> - shows the types of each column in table <name>\n"
		<< "> export <name> <filename> - saves a table in a file\n"
		<< "> addcolumn <table name> <column name> <column type> - adds an empty column to <table name>\n";
		
}
