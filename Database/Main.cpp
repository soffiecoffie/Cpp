#include <iostream>
#include <iomanip>
#include "Column.h"
#include "Table.h"
#include <string>


int main()
{
	int a1[4]{ 1,2,3,4 };
	std::string s1[4]{ "ice", "fire", "water", "earth" };

  Column<int> c1("integer", a1, 4);
	Column<std::string> c2("string", s1, 4);
	
  IColumn* iface[2]{ &c1, &c2};

	Table t1(iface, 2);
	t1.print();
	
  return 0;
}

