#ifndef MENU_H
#define MENU_H
#include <fstream>
#include "Player.h"
#include "Deck.h"

class Menu: public Deck
{
public:
	Menu();
	~Menu();

	void makeChoice(const char*);

	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;
	std::istream& readFromBin(std::istream&);
	std::ostream& writeToBin(std::ostream&) const;

	bool isExistingPlayer(const char*) const;
	bool over21(size_t) const;
	void findUserIndex(const char*);
	bool getEnd() const;

	void addPlayer(const char*, size_t);

	void printOptions() const;
	void printPlayers() const;
	void addDealerPoints(const Values&);

	size_t getSize() const;
	size_t getDealerPoints() const;
	size_t getUserInd() const;
	
	void updateCW();
	void updateGamesPlayed();
	void updateWins();
	void updatePlayerPoints(const Values&);
	void hit();
	void stand();
	void probability();
	void lose();
	void win();

private:
	size_t size;
	size_t userInd;
	Player* arr;
	size_t dealerPoints = 0;
	size_t DrawnCardsCount = 0;
	bool aceDrawn = 0;
	bool usedAce11value = 0;
	bool end = 0;
};

#endif
