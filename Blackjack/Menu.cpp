#include "Menu.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

Menu::Menu(): size(0), userInd(0), arr(nullptr)
{
}

Menu::~Menu()
{
	delete[] arr;
}

void Menu::makeChoice(const char* choice)
{
	assert(choice); //checks if it "has something inside"

	if (strcmp(choice, "Hit") == 0 || strcmp(choice, "hit") == 0) 
	{
		hit();
		return;
	}
	if (strcmp(choice, "Stand") == 0 || strcmp(choice, "stand") == 0)
	{
		stand();
		return;
	}
	assert(strcmp(choice, "Probability") == 0 || strcmp(choice, "probability") == 0); //if it gets this wrong then the input is definitely invalid!
	probability();
	return;
}

std::istream& Menu::read(std::istream& in)
{
	in >> size;
	int len;
	char* temp;
	double coef;

	arr = new Player[size];

	for (size_t i = 0; i < size; ++i)
	{
		in >> len;				

		temp = new char[len + 1];
		in.getline(temp, len + 1, '\n');

		arr[i].setName(temp);
		delete[] temp;

		in >> len; 
		arr[i].setWins(len);

		in >> coef;
		arr[i].setCW(coef);
	}
	return in;
}

std::ostream& Menu::write(std::ostream& out) const
{
	out << size << '\n';

	for (size_t i = 0; i < size; ++i)
	{
		out << strlen(arr[i].getName()) << arr[i].getName() << '\n';
		out << arr[i].getWins() << '\n' << arr[i].getCW() << '\n';
	}
	return out;
}

std::istream& Menu::readFromBin(std::istream& in)
{
	in >> size;
	arr = new Player[size];

	int len;
	double coef;

	for (size_t i = 0; i < size; ++i)
	{
		in >> len;

		char* temp = new char[len + 1];
		in.read(temp, len);
		temp[len] = '\0';
		arr[i].setName(temp);

		in >> len;
		arr[i].setAge(len);

		in >> len;
		arr[i].setWins(len);

		in >> len;
		arr[i].setGamesPlayed(len);

		in >> coef;
		arr[i].setCW(coef);
	}

	return in;
}


std::ostream& Menu::writeToBin(std::ostream& out) const
{
	out << size;
	out << '\n';

	for (size_t i = 0; i < size; ++i)
	{
		out << strlen(arr[i].getName());
		out.write(arr[i].getName(), strlen(arr[i].getName()));
		out << '\n';
		out << arr[i].getAge();
		out << '\n';
		out << arr[i].getWins();
		out << '\n';
		out << arr[i].getGamesPlayed();
		out << '\n';
		out << arr[i].getCW();
		out << '\n';
	}
	return out;
}

bool Menu::isExistingPlayer(const char* name) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (strcmp(arr[i].getName(), name) == 0) return true;
	}
	return false;
}

bool Menu::over21(size_t points) const
{
	return (arr[userInd].getPoints() + points) > 21;
}

void Menu::findUserIndex(const char* name) 
{
	if (isExistingPlayer(name)) 
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (strcmp(arr[i].getName(), name) == 0) 
			{
				userInd = i;
				return;
			}
		}
	}
}

bool Menu::getEnd() const
{
	return end;
}

void Menu::addPlayer(const char* name, size_t age)
{
	Player* temp = new Player[size];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = arr[i];
	}

	delete[] arr;
	arr = new Player[++size];
	for (size_t i = 0; i < size-1; ++i)
	{
		arr[i]=temp[i];
	}
	arr[size - 1].setName(name);
	arr[size - 1].setAge(age);

	userInd = size - 1;					//new change
}

void Menu::printOptions() const
{
	std::cout << "\n----------------------------------\n    What do you want to do now?\n----------------------------------\n"
		<< "1)\"Hit\"\n2)\"Stand\"\n3)\"Probability\"\n\nYour choice: ";
}

void Menu::printPlayers() const
{
	for (size_t i = 0; i < size; ++i)
	{
		arr[i].print();
		//arr[i].myPrint();
	}
}

void Menu::addDealerPoints(const Values& val) 
{
	size_t p;
	switch (val) {
	case Values::TWO:
		p = 2;
		break;
	case Values::THREE:
		p = 3;
		break;
	case Values::FOUR:
		p = 4;
		break;
	case Values::FIVE:
		p = 5;
		break;
	case Values::SIX:
		p = 6;
		break;
	case Values::SEVEN:
		p = 7;
		break;
	case Values::EIGHT:
		p = 8;
		break;
	case Values::NINE:
		p = 9;
		break;
	case Values::TEN:
	case Values::JACK:
	case Values::KING:
	case Values::QUEEN:
		p = 10;
		break;
	case Values::ACE:
		if (!aceDrawn) 
		{
			aceDrawn = 1;
			p = 11;
			if (dealerPoints + p > 21) 
			{
				p = 1;
			}
			else usedAce11value = 1;
		}
		else p = 1;
		break;
	}

	if (dealerPoints + p >= 17) 
	{
		if (dealerPoints + p > 21) 
		{
			if (usedAce11value)
			{
				dealerPoints -= 10;
				dealerPoints += p;

				std::cout << "(Points: " << dealerPoints << ")\n";

				usedAce11value = 0;
			}
			else {
				
				dealerPoints += p;
				std::cout << "(Points: " << dealerPoints << ")\n";			

				win();				//the user wins and the dealer loses
				return;
			}
		}
		else {
			dealerPoints += p;
			std::cout << "(Points: " << dealerPoints << ")\n";
		}

		if (dealerPoints >= 17 && dealerPoints <= 21) //asking again because the points might have become less if i used an ace as 11
		{			
			if (dealerPoints > arr[userInd].getPoints()) 
			{
				lose();  //dealer wins, you lose
				return;
			}
			else if (dealerPoints <= arr[userInd].getPoints())
			{
				win();  //you win, dealer loses
				return;
			}
		}
	}
	else 
	{
		dealerPoints += p;
		std::cout << "(Points: " << dealerPoints << ")\n";
	}
}
	
size_t Menu::getSize() const
{
	return size;
}

size_t Menu::getDealerPoints() const
{
	return dealerPoints;
}

size_t Menu::getUserInd() const
{
	return userInd;
}

void Menu::updateCW()
{
	double coef = arr[userInd].getWins();
	coef /= arr[userInd].getGamesPlayed();
	
	arr[userInd].setCW(coef);
}

void Menu::updateGamesPlayed()
{
	arr[userInd].setGamesPlayed(arr[userInd].getGamesPlayed() + 1);
}

void Menu::updateWins()
{
	arr[userInd].setWins(arr[userInd].getWins() + 1);
}

void Menu::updatePlayerPoints(const Values& val)
{
	size_t p;
	switch (val) {
	case Values::TWO:
		p = 2;
		break;
	case Values::THREE:
		p = 3;
		break;
	case Values::FOUR:
		p = 4;
		break;
	case Values::FIVE:
		p = 5;
		break;
	case Values::SIX:
		p = 6;
		break;
	case Values::SEVEN:
		p = 7;
		break;
	case Values::EIGHT:
		p = 8;
		break;
	case Values::NINE:
		p = 9;
		break;
	case Values::TEN:
		p = 10;
		break;
	case Values::JACK:
		p = 10;
		break;
	case Values::KING:
		p = 10;
		break;
	case Values::QUEEN:
		p = 10;
		break;
	case Values::ACE:
		if (!aceDrawn)
		{
			aceDrawn = 1;
			p = 11;
			if (over21(p)) 
			{
				p = 1;
			}
			else usedAce11value = 1;
		}
		else p = 1;
		break;
	}

	if (over21(p))
	{
		if (usedAce11value)
		{
			arr[userInd].setPoints(arr[userInd].getPoints() - 10);
			arr[userInd].addPoints(p);

			std::cout << "(Points: " << arr[userInd].getPoints() << ")\n";
			usedAce11value = 0;
		}
		else {
			arr[userInd].addPoints(p);									
			std::cout << "(Points: " << arr[userInd].getPoints() << ")\n";

			lose();
		}
	}
	else {
		arr[userInd].addPoints(p);
		std::cout << "(Points: " << arr[userInd].getPoints() << ")\n";
	}

	if (arr[userInd].getPoints() == 21)
	{
		win();
	}
}

void Menu::hit()
{
	std::cout << "You drew: ";
	Card drawnCard(draw());
	drawnCard.print();
	
	++DrawnCardsCount;

	updatePlayerPoints(drawnCard.getValue());
}

void Menu::stand()
{
	aceDrawn = 0;				 //so that i can use these for the dealer as well
	usedAce11value = 0;			 //

	std::cout << "-----Dealer's turn-----\n";

	do {
		std::cout << "Dealer drew: ";
		Card drawnCard(draw());
		drawnCard.print();
	
		++DrawnCardsCount;

		addDealerPoints(drawnCard.getValue());
	} while (dealerPoints < 17);
}

void Menu::probability()
{
	int n = 21 - arr[userInd].getPoints();
	if (n > 11) {
		std::cout << "Probability: 0.0";
		return;
	}

	Values val;

	switch (n) {
	case 1:
		Values::ACE;
		break;
	case 2:
		val = Values::TWO;
		break;
	case 3:
		val = Values::THREE;
	case 4:
		val = Values::FOUR;
		break;
	case 5:
		val = Values::FIVE;
		break;
	case 6:
		val = Values::SIX;
		break;
	case 7:
		val = Values::SEVEN;
		break;
	case 8:
		val = Values::EIGHT;
		break;
	case 9:
		val = Values::NINE;
		break;
	case 11:
		Values::ACE;
		break;
	default:
		break;
	}

	double result = 0;
	size_t notDrawnCount = Deck::getSize() - DrawnCardsCount;

	if (n == 10) {
		result += rank_count(Values::JACK);	  
		result += rank_count(Values::KING);	  
		result += rank_count(Values::QUEEN);  
		result += rank_count(Values::TEN);	  
	}										  
	else result = rank_count(val);		      

	result /= notDrawnCount;

	std::cout << "Probability: " << std::setprecision(2) << result << '\n';
}

void Menu::lose()
{
	assert(arr[userInd].getPoints() > 21 || (dealerPoints > arr[userInd].getPoints() && dealerPoints <= 21));
	std::cout << "YOU LOST! :(\n";
	
	updateGamesPlayed();
	updateCW();
	end = 1;
}

void Menu::win()
{
	assert(arr[userInd].getPoints() == 21 || dealerPoints > 21 || (arr[userInd].getPoints() >= dealerPoints && arr[userInd].getPoints() <= 21));
	std::cout << "YOU WON! :)\n";

	updateGamesPlayed();
	updateWins();
	updateCW();
	end = 1;
}
