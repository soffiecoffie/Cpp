#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include "Deck.h"


void Deck::makeDefaultDeck()
{		
	int ind = 0;
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 13; ++j)
		{
			deck[ind++] = Card(i, j);
		}
	}
}

void Deck::makeCustomSizedDeck(size_t k)
{
	Card c;
	size_t max = floor(((k - 1) / 52) + 1);
	for (size_t i = 0; i < k; ++i)
	{
		c.setRandSuit();
		c.setRandVal();
		if (repeatsCount(c, i) < max) //checks how many times it repeats up until this point;
			deck[i] = c;

		else --i; //assures that if it repeats more times than wanted it will not skip adding a card, making the deck shorter

	}
}

void Deck::setDeckSerialNumber(const char* snum)
{
	assert(snum && strlen(snum) <= 10);

	if (serialNumber) 
	{
		if (strcmp(serialNumber, "Default") == 0)
			delete[] serialNumber;
	}
	
	for (size_t i = 0; i < size; ++i)
	{
		deck[i].finishSerialNumber(snum, i);
	}

	serialNumber = new char[strlen(snum) + 1];
	strcpy(serialNumber, snum);
}

void Deck::setDeckSize(size_t newSize)
{
	assert(newSize != 52); //i only want to set a size if the deck is supposed to be custom
	size = newSize;

	delete[] deck;
	//delete[] serialNumber;

	deck = new Card[newSize];
	makeCustomSizedDeck(newSize);
}

void Deck::printDeck() const
{
	for (size_t i = 0; i < size; ++i)
	{
		deck[i].print();
		std::cout << '\n';
	}
}

void Deck::swap(size_t a, size_t b)
{
	assert(a <= size - 1 && b <= size - 1);
	Card temp(deck[a]);
	deck[a] = deck[b];
	deck[b] = temp;
}

void Deck::shuffle()
{
	int ind1;
	int ind2;
	for (size_t i = 0; i < size; ++i) 
	{
		ind1 = rand() % 52;
		ind2 = rand() % 52;
		if (ind1 == ind2) 
		{
			--i; //so it will deffinitely make some change
		}
		else swap(ind1, ind2);
	}
}

Card& Deck::draw()
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		swap(i, i + 1);
	}

	deck[size - 1].setDrawn(1);

	return deck[size - 1];
}

size_t Deck::rank_count(const Values& val) const
{
	size_t counter = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (deck[i].getValue() == val && !deck[i].getDrawn()) ++counter;
	}

	return counter;
}

size_t Deck::getSize() const
{
	return size;
}

size_t Deck::suit_count(const Suits& suit) const
{
	size_t counter = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (deck[i].getSuit() == suit) ++counter;
	}

	return counter;
}

size_t Deck::repeatsCount(const Card& c, size_t size)
{
	int counter = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (deck[i] == c) ++counter;
	}
	return counter;
}

char* Deck::getSerialNumber() const
{
	char* result = new char[strlen(serialNumber) + 1];
	strcpy(result, serialNumber);
	return result;
}


Deck::Deck() :size(52)
{
	deck = new Card[52];
	makeDefaultDeck();

	setDeckSerialNumber("Default");

	for (size_t i = 0; i < 52; ++i)
	{
		deck[i].finishSerialNumber("Default", i);
	}

	shuffle();
}

Deck::Deck(size_t k) :size(k)
{
	deck = new Card[k];
	makeCustomSizedDeck(k);

	setDeckSerialNumber("Custom");

	for (size_t i = 0; i < k; ++i)
	{
		deck[i].finishSerialNumber(serialNumber, i);
	}
}

Deck::Deck(size_t k, const char* snum) :size(k)
{
	deck = new Card[k];
	makeCustomSizedDeck(k);
	
	setDeckSerialNumber(snum);  

	for (size_t i = 0; i < k; ++i)
	{
		deck[i].finishSerialNumber(serialNumber, i);
	}
}

Deck::~Deck()
{
	delete[] serialNumber;
	delete[] deck;
}
