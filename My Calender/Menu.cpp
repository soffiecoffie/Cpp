/*

                              STILL NOT COMPLETE

*/

#include "Menu.h"
//#include "Com.h"
#include <fstream>
#include <iostream>


char* copyDynamic(const char* other) {
	char* result = new char[strlen(other) + 1];
	strcpy(result, other);
	return result;
}

bool Menu::isValid(int n)
{
	return n >= 1 && n <= 4; //if i have only 4 commands!!
}

Menu::Menu() : input(0), myFileName(nullptr), userFileName(nullptr), isDone(0)
{
}

Menu::Menu(int n): myFileName(nullptr), userFileName(nullptr), isDone(0)  // const char* myName, const char* userName)
{
	setInput(n);
	
	//setMyFileName(myName);
	//setUserFileName(userName);
}

void Menu::setInput(int n)
{
	input = n;
	do {
		if (!isValid(input)) {
			std::cout << "\nInvalid input, please try again: ";
			std::cin >> input;

			while (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(265, '\n');
				std::cout << "\nInvalid input, please enter a digit from 1 to 4: " << std::endl;
				std::cin >> input;
			}
		}
	} while (!isValid(input));
}

void Menu::setMyFileName(const char* other)
{
	delete[] myFileName;
	myFileName = copyDynamic(other);
}

void Menu::setUserFileName(const char* other)
{
	delete[] userFileName;
	userFileName = copyDynamic(other);
}

void Menu::choice()
{
	enum Commands {//keep here or in .h?
		open = 1, save, saveAs, close
	};

	//no default case because the input is valid and it wont ever go in a default case
	switch (input) {
	case open: std::cout << "You chose \"open\"\n";
		this->open();
		break;
	case save: std::cout << "You chose \"save\"\n";
		this->save();
		break;
	case saveAs: std::cout << "You chose \"save as\"\n";
		this->saveAs();
		break;
	case close: std::cout << "You chose \"close\"\n";
		this->close();
		break;
	}
}

bool Menu::getIsDone() const
{
	return isDone;
}

void Menu::printOptions() const
{
	std::cout << "\n---------------------------------\nALL OPTIONS - pick a number\n---------------------------------\n"
		<< "(1) - open\n" << "(2) - save\n" << "(3) - save as\n" << "(4) - close\n---------------------------------\n";
}

void Menu::open()
{
	//temporary maybe you should make this name as a default:// or should i make them give me a name of an empty file
	setMyFileName("memory.txt");
	std::ofstream myFile(myFileName);

	if (!myFile) {
		std::cout << "Uh oh, something went wrong, there are system problems :("; //what happens if this situation comes up? and can it come up
		return;
	}

	char* name = new char[30];
	
	//assures that the user doesnt write a name with more than 30symb
	do {
		std::cout << "Please input the name of the file you wish to open (less than 30 symbols!): ";
		std::cin >> name;
	} while (strlen(name) >= 30);

	setUserFileName(name);

	std::ifstream someFile;
	someFile.open(userFileName);

	//nqma da izleze dokato ne uspee da otvori faila na potrebitelq
	while (!someFile) {
		std::cout << "Can't open file " << userFileName << ", please try again: "; //what happens if this situation comes up? 
		std::cin >> name;
		setUserFileName(name);
		someFile.open(userFileName);//can i open a different name?
	}

					//prenasq teksta ot user file-a kum file-a, koito zapazva informaciqta i pravi promeni
	char ch;		//would it better if i did it with string, will it be faster?
	while (someFile) {
		someFile.get(ch);
		myFile << ch;
	}
}

void Menu::saveHelper(const char * outName, const char* inName) {
	std::ofstream userFile(outName, std::ios::trunc | std::ios::out);
	if (!userFile) {					//is this needed if im just opening for writing?
		std::cout << "Uh oh, can't open your file, something went wrong"; //what happens if this situation comes up? and can it come up
		return;
	}//in if saveAs file cant be opened? or already exists but isnt name nooo probs not

	std::ifstream myFile(inName);// do i need guards here?
	if (!myFile) {
		std::cout << "Uh oh, something went wrong, all changes can be found in the system file"; //what happens if this situation comes up? and can it come up
		return;
	}

	//make separate func for this
	char ch;
	while (myFile) {
		myFile.get(ch);
		userFile << ch;
	}
	//do i need more guards				//check what causes each file fail and test it one by one
}
void Menu::save()
{

	saveHelper(userFileName, myFileName);
	/*
	std::ofstream userFile(userFileName, std::ios::trunc | std::ios::out);
	if (!userFile) {					//is this needed if im just opening for writing?
		std::cout << "Uh oh, can't open your file, something went wrong"; //what happens if this situation comes up? and can it come up
		return;
	}

	std::ifstream myFile(myFileName);// do i need guards here?
	if (!myFile) {
		std::cout << "Uh oh, something went wrong, all changes can be found in the system file"; //what happens if this situation comes up? and can it come up
		return;
	}

	//make separate func for this
	char ch;
	while (myFile) {
		myFile.get(ch);
		userFile << ch;
	}
	//do i need more guards				//check what causes each file fail and test it one by one
	*/
}


//save as command, maybe i should remove it and keep the save option
//and when i want to save it in a dif file id create new filename and put it here
//should also check if it's the same name as the first cause i should not be allowed to have 
//two files with the same name and obviously the user chose saveAS so it shouldnt be the same file

void Menu::saveAs() {
	char* name = new char[30];

	//assures that the user doesnt write a name with more than 30symb
	do {
		std::cout << "\nPlease input the name of the file you wish to save it as: ";
		std::cin >> name;
		if (strcmp(name, userFileName) == 0) {
			std::cout << "\nA file with the name \"" << name << "\" already exists! Please choose a different name!\n";
		}
	} while (strlen(name) >= 30 || strcmp(name,userFileName)==0);

	saveHelper(name, myFileName);
}

void Menu::close()
{
	std::cout << "No changes were made to your calendar.";
	isDone = 1;
	std::ofstream myFile(myFileName, std::ios::trunc);				//it automatically closes right? after leaving the function
}
