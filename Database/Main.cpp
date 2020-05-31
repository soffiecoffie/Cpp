#include <iostream>
#include "Database.h"

int main()
{
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
