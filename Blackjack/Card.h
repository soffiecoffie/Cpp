#ifndef CARD_H
#define CARD_H
#include "Suits.h"
#include "Values.h"

int digits(int, int = 0);
char* turnNumIntoChar(int num);

class Card
{
public:
	Suits getSuit() const;
	Values getValue() const;
	char* getSerialNumber() const;
	bool getDrawn() const;

	void setSuit(const Suits&);
	void setValue(const Values&);
	void setRandSuit();
	void setRandVal();
	void setSerialNumber(const char*);
	void finishSerialNumber(const char*, size_t);//adds a number at the end of the deck serial number
	void setDrawn(bool);

	void print() const;
	Card& operator=(const Card&);
	bool operator==(const Card&);

	Card();
	Card(const Suits&, const Values&, const char*);
	Card(const Suits&, const Values&);
	Card(size_t, size_t);
	Card(const Card&);
	~Card() { delete[] serialNumber; }

private:
	Suits suit;
	Values value;
	char* serialNumber;
	bool drawn = 0;
};

#endif
