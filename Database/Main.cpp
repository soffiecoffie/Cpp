#include <iostream>
#include "Database.h"

int main()
{
	double* s = new double[5]{ -0.5,+23.3,-481.184,49.15, 4.0 };
	Column<double> d("DoubleTrouble","double", s, 5);
	d.print();
	std::cout << "Welcome!\nTo create a new or open an existing database write open <filename>:\n\n";
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
	return 0;
}
