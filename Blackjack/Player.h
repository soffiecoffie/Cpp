#ifndef PLAYER_H
#define PLAYER_H
#include<fstream>

class Player
{
public:
	void setName(const char*);
	void setAge(size_t);
	void setWins(size_t);
	void setPoints(size_t);
	void addPoints(size_t);
	void setGamesPlayed(size_t);
	void setCW(double);

	double getCW() const;
	size_t getWins() const;
	size_t getPoints() const;
	size_t getAge() const;
	size_t getGamesPlayed() const;
	char* getName() const;
	void myPrint() const;
	void print() const;
	
	Player& operator=(const Player&);

	size_t spaceCount(const char*) const;
	bool isValidSpace(const char*) const;


	std::istream& read(std::istream&);
	std::ostream& write(std::ostream&) const;				

	friend std::istream& operator>>(std::istream&, Player&);
	friend std::ostream& operator<<(std::ostream&, const Player&);

	Player();
	Player(size_t, const char*);
	Player(size_t, size_t, double, const char*);
	~Player();

private:
	size_t age;
	size_t wins = 0;
	size_t points = 0; //current points every new game makes it start from 0
	size_t gamesPlayed = 0; //numbers of games played

	double CW = 0; //coefficient of wins 
	char* name;

};

#endif 
