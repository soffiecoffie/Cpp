#include <iostream>
#include <fstream>
#include <iomanip>
//#include "Column.h"
#include "Table.h"
#include "Invoker.h"
#include "IDatabase.h"
#include "Database.h"
#include <string>
/*
if pagecmd is on only next previous and out should work
*/

int main()
{
	Database db;

	IDatabase* ptr = &db;
	Invoker invoker(ptr);

	std::string input;
	while (!ptr->getIsDone())
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		invoker.executeCmd(input);
	}
	std::cout << std::endl;

	//Database db1;
	//
//	//ITable* t1 = &t12;
	//
	//std::ifstream in("DB1.txt");
	//db1.read(in);
	//in.close();
	////db1.write(std::cout);
	//db1.import("Table1.txt");
	//db1.showtables();
	//db1.describe("Food");
	//db1.myExport("Food","foodforthought.txt");
	//std::ofstream out("DB2.txt");
	//db1.write(out);
	//in.close();
	//db1.showtables();

//''	Table t12;
//''	ITable* t1=&t12;
//''//	t1.print(std::cout);
//''//	c2.print();
//''//	delete [] iface;
//''
//''//	std::ofstream out("Table1.txt");
//''//	t1.write(out);
//''//	out.close();
//''
//''	std::ifstream in("hard.txt");
//''	t1->read(in);
//''	in.close();
//''	t1->print(std::cout);
	
	
	//	int size;
//	std::cin >> size;
	
	//std::string** arr = new std::string *[size];
	//for (size_t i = 0; i < size; i++)
	//{
	//	arr[i] = new std::string("120");
	//}
	//
	//for (size_t i = 0; i < size; i++)
	//{
	//	std::cout << *arr[i];
	//}
	//arr[0] = nullptr;
	//std::cout << (arr[0] == nullptr);
	//for (int i = 0; i < size; i++) {
	//	delete arr[i];
	//}
	//delete[] arr;
	//Column<int> a;
	
	//int a=0;
	//std::string s = NULL;
	//std::cout << s;
	//IColumn* col = new Column<int>();
	//col->addCell("  235 ");
	//col->printCell(0);
	//col->Column<int>::getCellLength(0);
	//IColumn* col;
	//col = new Column<std::string>("string");
	//col->Column<std::string>::getType();


//	std::string s1[12]{ "Fire", "Water", "Earth", "Air", "Stone", "Energy", "Spirit", "Metal", "Gold", "Phil's Stone","Ice" };
//	std::string s2[10]{ "pane", "halp", "sHESnotOK", "deap", "live", "love", "laugh", "such", "good", "nice" };
//	Column<std::string> c2("Elements", "string", s1, 10);
//	Column<std::string> c3("Straw", "string", s2, 10);
//	c2.setNullCellAt(2);
//
//	IColumn** arr = new IColumn * [2]{
//		new Column<std::string>("Elements", "string", s1, 11),
//		new Column<std::string>("Straw", "string", s2, 10) };
//
//	Table t(arr, 2, "Fabulousou");
//	t.addCol("amigos", "string");
//	//Table t(
//	//	new IColumn * [2]{
//	//	new Column<std::string>("Elements", "string", s1, 10),
//	//	new Column<std::string>("Elements", "string", s1, 6) },
//	//	2, "Name"
//	//	);
//	t.print(std::cout);
//	t.print(std::cout);
//	delete[] arr;



//	c2.print();
//	int a1[10]{ 1,2,3,4,5,6,7,8,9,10};
//	//std::string s1[4]{ "ice", "fire", "water", "earth" };
//	Column<int> c1("integer", "int", a1, 10);
//	//Column<std::string> c2("string", "string", s1, 4);
//	//c2.print();
//	IColumn* iface[2]{ &c1, &c2};
//	Table t1 (iface, 2, "Random");
//	t1.print(std::cout);
	//c2.print();
	//delete [] iface;
	
	//std::ofstream out("Table1.txt");
	//t1.write(out);
	//out.close();
	
//	std::ifstream in("Table1.txt");
//	t1.read(in);
//	in.close();
	//t1.print(std::cout);

	return 0;
}

/*
#include <iostream>
#include <fstream>
#include <iomanip>
//#include "Column.h"
#include "Table.h"
#include <string>


int main()
{
//	int size;
//	std::cin >> size;

	//std::string** arr = new std::string *[size];
	//for (size_t i = 0; i < size; i++)
	//{
	//	arr[i] = new std::string("120");
	//}
	//
	//for (size_t i = 0; i < size; i++)
	//{
	//	std::cout << *arr[i];
	//}
	//arr[0] = nullptr;
	//std::cout << (arr[0] == nullptr);
	//for (int i = 0; i < size; i++) {
	//	delete arr[i];
	//}
	//delete[] arr;
	//Column<int> a;

	//int a=0;
	//std::string s = NULL;
	//std::cout << s;
	//IColumn* col = new Column<int>();
	//col->addCell("  235 ");
	//col->printCell(0);
	//col->Column<int>::getCellLength(0);
	//IColumn* col;
	//col = new Column<std::string>("string");
	//col->Column<std::string>::getType();
	std::string s1[10]{ "Fire", "Water", "Earth", "Air", "Stone", "Energy", "Spirit", "Metal", "Gold", "Phil's Stone" };
	Column<std::string> c2("Elements", "string", s1, 10);
	Column<std::string> c3("Elements", "string", s1, 6);
	c2.setNullCellAt(2);

	IColumn** arr = new IColumn * [2]{
		new Column<std::string>("Elements", "string", s1, 10),
		new Column<std::string>("Elements", "string", s1, 6) };

	Table t(arr, 2, "Fabulousou");
	//Table t(
	//	new IColumn * [2]{
	//	new Column<std::string>("Elements", "string", s1, 10),
	//	new Column<std::string>("Elements", "string", s1, 6) },
	//	2, "Name"
	//	);
	t.print(std::cout);

	delete[] arr;
//	c2.print();
//	int a1[10]{ 1,2,3,4,5,6,7,8,9,10};
//	//std::string s1[4]{ "ice", "fire", "water", "earth" };
//	Column<int> c1("integer", "int", a1, 10);
//	//Column<std::string> c2("string", "string", s1, 4);
//	//c2.print();
//	IColumn* iface[2]{ &c1, &c2};
//	Table t1 (iface, 2, "Random");
//	t1.print(std::cout);
	//c2.print();
	//delete [] iface;

	//std::ofstream out("Table1.txt");
	//t1.write(out);
	//out.close();

//	std::ifstream in("Table1.txt");
//	t1.read(in);
//	in.close();
	//t1.print(std::cout);

	return 0;
}




*/