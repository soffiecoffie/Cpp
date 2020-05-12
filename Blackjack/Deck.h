#ifndef DECK_H
#define DECK_H
#include "Card.h"

class Deck
{
public:
	void makeDefaultDeck();
	void makeCustomSizedDeck(size_t);
	void setDeckSerialNumber(const char*);  
	void setDeckSize(size_t);
	void printDeck() const;
	void swap(size_t, size_t);
	void shuffle();
	Card& draw(); 
	size_t suit_count(const Suits&) const;
	size_t rank_count(const Values&) const;
	size_t getSize() const;

	size_t repeatsCount(const Card&, size_t);  
	char* getSerialNumber() const;

	Deck();
	Deck(size_t);
	Deck(size_t, const char*);
	~Deck();

private:
	size_t size;
	char* serialNumber; 
	Card* deck;
};

#endif
