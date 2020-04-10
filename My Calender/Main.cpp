/*


                        STILL WORKING ON IT
*/
#include <iostream>
#include <fstream>
#include "Com.h"
#include "Menu.h"

//void choiceActions(int choice, std::ofstream& myFile, char* userFile, std::ifstream& someFile);
//void open1(std::ifstream& fileName, std::ofstream& myFile);

int main()
{
	std::cout << "Welcome to your personal calendar!\n----------------------------------\n\nTo open your calendar write \"1\"\nTo exit write \"4\"\n";

	std::ofstream myFile("custom.txt");
	std::ifstream userFile;
	
	int choice;
	
	do {
		std::cout << "\nYour choice: ";
		std::cin >> choice;

		//is this needed?
		while (std::cin.fail()) //if someone puts letters/words in the choice variable instead of numbers
		{
			std::cin.clear();
			std::cin.ignore(265, '\n');
			std::cout << "\nInvalid input, please enter a digit: " << std::endl;
			std::cin >> choice;
		}

	} while (choice != 1 && choice != 4);

	//should i be able to open again right after opening and what happens i think it will just change the opened file
	Menu menu(choice);
	do {
		menu.choice();
		std::cout << "\nWhat do you want to do next?";
		menu.printOptions();
		std::cin >> choice;

		//add seperate func for this
		while (std::cin.fail()) //if someone puts letters/words in the choice variable instead of numbers
		{
			std::cin.clear();
			std::cin.ignore(265, '\n');
			std::cout << "\nInvalid input, please enter a digit from 1 to 4: " << std::endl;
			std::cin >> choice;
		}

		menu.setInput(choice);

		if (choice == 4) menu.choice();

	} while (!menu.getIsDone());



	return 0;
}
