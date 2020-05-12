#include <iostream>
#include <fstream>
#include "Deck.h"
#include <cstring>
#include <ctime>
#include "Menu.h"

int main()
{
	srand(time(0));

	std::cout << "Welcome to my simulation of Blackjack!\n--------------------------------------\n\n";

	const char* playersFile = "playerFile.bin";
	Menu menu;

	std::ifstream in(playersFile, std::ios::binary | std::ios::in);
	
	if (!in) std::cout << "Can't open file " << playersFile << "!\n";
	else menu.readFromBin(in);
	
	in.close();
	
	if (menu.getSize() == 1) std::cout << "------------PREVIOUS PLAYER------------\n";
	else if (menu.getSize() > 1) std::cout << "--------------ALL PLAYERS-------------\n";
	else std::cout << "--NO PREVIOUS PLAYERS TO CHOOSE FROM--";

	menu.printPlayers();

	std::cout << "\nChoose a player or enter a new one: ";
	char* name = new char[30];				
	std::cin.getline(name, 30, '\n');

	
	if (menu.isExistingPlayer(name)) 
	{
		menu.findUserIndex(name);
		std::cout << "\nWelcome back, " << name << "!\n";
	}
	else
	{
		size_t age;
		std::cout << "Please enter your age " << name << ":\n";
		std::cin >> age;

		while (std::cin.fail()) //if someone puts letters/words in the age instead of numbers
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "\nInvalid input, please enter an age in numbers: " << std::endl; 
			std::cin >> age;
		}

		if (age < 18)
		{
			std::cout << "You're too young to play! Come back when you're older :)";
			return 0;
		}
		else if (age > 90)
		{
			std::cout << "Sorry, you can't play :(";
			return 0;
		}
		
		menu.addPlayer(name, age);
		std::cout << "You will play as " << name << '\n';
	}
	
	size_t deckSize;
	std::cout << "\nChoose the size of the deck: ";
	std::cin >> deckSize;

	while (std::cin.fail()) //if someone puts letters/words in the deckSize variable instead of numbers
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "\nInvalid input, please enter a deck size in numbers: " << std::endl; 
		std::cin >> deckSize;
	}
	
	if (deckSize != 52) 
	{
		menu.setDeckSize(deckSize);
	
		char* answer = new char[11];				
		
		std::cout << "\nIf you want to choose a serial number for the deck, input the\nserial number you want (in <= 10 symbols), else write \"no\": ";
		std::cin.ignore(1, '\n');

		std::cin.getline(answer, 11, '\n');

		if (strcmp(answer, "no") == 0)
		{
			menu.setDeckSerialNumber("Custom");
		}
		else 
		{
			menu.setDeckSerialNumber(answer);
		}

		delete[] answer;
	}
	else std::cin.ignore(1, '\n');
	
	//menu.printDeck();
	//std::cout << menu.getSerialNumber();			//deck's serial number

	std::cout << "\n--------------Start!--------------\n\n";
	menu.hit();

	char* userInput = new char[12];

	do {
		menu.printOptions();
		std::cin.getline(userInput, 12, '\n');
		
		//std::cout << "\nYou chose " << userInput;		
		
		std::cout << std::endl;
		menu.makeChoice(userInput);
	} while (!menu.getEnd());

	//UPDATING PLAYER FILE
	std::ofstream out(playersFile, std::ios::binary | std::ios::out | std::ios::trunc);
	if(!out) std::cout<<"Error: Can't open player file, info can't be updated!";
	menu.writeToBin(out);
	out.close();

	delete[] userInput;
	delete[] name;

	return 0;
}
