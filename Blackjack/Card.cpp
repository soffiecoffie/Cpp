#include "Card.h"
#include <iostream>
#include <cstring>
#include <cassert>

Suits Card::getSuit() const
{
	return suit;
}

Values Card::getValue() const
{
	return value;
}

char* Card::getSerialNumber() const
{
	char* result = new char[strlen(serialNumber) + 1];
	strcpy(result, serialNumber);
	return result;
}

bool Card::getDrawn() const
{
	return drawn;
}

void Card::setSuit(const Suits& nsuit)
{
	suit = nsuit;
}

void Card::setValue(const Values& val)
{
	value = val;
}

void Card::setRandVal()
{
	int n = rand() % 12;

	switch (n) {
	case 0:
		value = Values::TWO;
		break;
	case 1:
		value = Values::THREE;
		break;
	case 2:
		value = Values::FOUR;
		break;
	case 3:
		value = Values::FIVE;
		break;
	case 4:
		value = Values::SIX;
		break;
	case 5:
		value = Values::SEVEN;
		break;
	case 6:
		value = Values::EIGHT;
		break;
	case 7:
		value = Values::NINE;
		break;
	case 8:
		value = Values::TEN;
		break;
	case 9:
		value = Values::JACK;
		break;
	case 10:
		value = Values::QUEEN;
		break;
	case 11:
		value = Values::QUEEN;
		break;
	case 12:
		value = Values::ACE;
		break;
	}
}

void Card::setRandSuit()
{
	int n = rand() % 4;

	switch (n) {
	case 0:
		suit = Suits::CLUBS;
		break;
	case 1:
		suit = Suits::DIAMONDS;
		break;
	case 2:
		suit = Suits::HEARTS;
		break;
	case 3:
		suit = Suits::SPADES;
		break;
	}
}

void Card::setSerialNumber(const char* snum)
{
	assert(snum && strlen(snum) <= 15);

	//delete[] serialNumber;
	serialNumber = new char[strlen(snum) + 1];
	strcpy(serialNumber, snum);
}

void Card::finishSerialNumber(const char* word, size_t num)
{
	assert((strlen(word) + digits(num)) <= 15);

	delete[] serialNumber;
	serialNumber = new char[strlen(word) + digits(num) + 1];

	strcpy(serialNumber, word);
	
	char* ch = new char[digits(num) + 1];
	ch = turnNumIntoChar(num);					
	
	strcat(serialNumber, ch);
}

void Card::setDrawn(bool n)
{
	drawn = n;
}

Card::Card() : suit(Suits::CLUBS), value(Values::TWO)
{
	serialNumber = nullptr;
}

Card::Card(const Suits& suit, const Values& value, const char* snum) : suit(suit), value(value)
{
	setSerialNumber(snum);		
}

Card::Card(const Suits& suit, const Values& value) : suit(suit), value(value), serialNumber(nullptr)
{
}

Card::Card(size_t s, size_t v)
{
	switch (v) {
	case 0:
		value = Values::TWO;
		break;
	case 1:
		value = Values::THREE;
		break;
	case 2:
		value = Values::FOUR;
		break;
	case 3:
		value = Values::FIVE;
		break;
	case 4:
		value = Values::SIX;
		break;
	case 5:
		value = Values::SEVEN;
		break;
	case 6:
		value = Values::EIGHT;
		break;
	case 7:
		value = Values::NINE;
		break;
	case 8:
		value = Values::TEN;
		break;
	case 9:
		value = Values::JACK;
		break;
	case 10:
		value = Values::KING;
		break;
	case 11:
		value = Values::QUEEN;
		break;
	case 12:
		value = Values::ACE;
		break;
	}

	switch (s) {
	case 0:
		suit = Suits::CLUBS;
		break;
	case 1:
		suit = Suits::DIAMONDS;
		break;
	case 2:
		suit = Suits::HEARTS;
		break;
	case 3:
		suit = Suits::SPADES;
		break;
	}

	serialNumber = nullptr;
}

Card::Card(const Card& other): suit(other.suit), value(other.value)
{
	setSerialNumber(other.serialNumber);
}


void Card::print() const
{
	switch (value) {
	case Values::TWO:
		std::cout << "2 ";
		break;
	case Values::THREE:
		std::cout << "3 ";
		break;
	case Values::FOUR:
		std::cout << "4 ";
		break;
	case Values::FIVE:
		std::cout << "5 ";
		break;
	case Values::SIX:
		std::cout << "6 ";
		break;
	case Values::SEVEN:
		std::cout << "7 ";
		break;
	case Values::EIGHT:
		std::cout << "8 ";
		break;
	case Values::NINE:
		std::cout << "9 ";
		break;
	case Values::TEN:
		std::cout << "10 ";
		break;
	case Values::JACK:
		std::cout << "J ";
		break;
	case Values::KING:
		std::cout << "K ";
		break;
	case Values::QUEEN:
		std::cout << "Q ";
		break;
	case Values::ACE:
		std::cout << "A ";
		break;
	}


	switch (suit) {
	case Suits::CLUBS:
		std::cout << "(clubs) ";
		break;
	case Suits::DIAMONDS:
		std::cout << "(diamonds) ";
		break;
	case Suits::HEARTS:
		std::cout << "(hearts) ";
		break;
	case Suits::SPADES:
		std::cout << "(spades) ";
		break;
	}

	//std::cout << " Serial Num:" << serialNumber;
}

Card& Card::operator=(const Card& other)
{
	if (this != &other)
	{
		suit = other.suit;

		value = other.value;

		drawn = other.drawn;

		if (other.serialNumber)// != nullptr)
		{
			delete[] serialNumber;
			setSerialNumber(other.serialNumber);
		}
	}

	return *this;
}

bool Card::operator==(const Card& other) //checks for the same card in suits and values not serialnum
{
	return suit == other.suit && value == other.value;
}


char* turnNumIntoChar(int num)
{
	int size = digits(num);
	char* ch = new char[size + 1];
	for (int i = size - 1; i >= 0; --i)
	{
		ch[i] = num % 10 + '0';
		num /= 10;
	}
	ch[size] = '\0';
	return ch;
}

int digits(int n, int count)
{
	if (n / 10 == 0) return ++count;
	n /= 10;
	++count;
	return digits(n, count);
}

