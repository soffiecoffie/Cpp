#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <iomanip>

void Player::setName(const char* name)
{

	assert(name[0] >= 'A' && name[0] <= 'Z' && isValidSpace(name));
	
	size_t ind = 0;
	for (size_t i = 0; i < strlen(name); ++i)
	{
		if (name[i] == ' ') 
		{
			ind = i + 1;
			break;
		}
	}

	assert(name[ind] >= 'A' && name[ind] <= 'Z');

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Player::setAge(size_t age)
{
	assert(age >= 18 && age <= 90);
	this->age = age;
}

void Player::setWins(size_t wins)
{
	this->wins = wins;
}

void Player::setPoints(size_t p)
{
	points = p;
}

void Player::addPoints(size_t p)
{ 
	points += p;
}

void Player::setGamesPlayed(size_t n)
{
	gamesPlayed = n;
}

void Player::setCW(double coef)
{
	assert(coef >= 0 && coef <= 1);
	CW = coef;
}

double Player::getCW() const
{
	return CW;
}

size_t Player::getWins() const
{
	return wins;
}

size_t Player::getPoints() const
{
	return points;
}

size_t Player::getAge() const
{
	return age;
}

size_t Player::getGamesPlayed() const
{
	return gamesPlayed;
}

char* Player::getName() const
{
	return name;
}

void Player::myPrint() const
{
	std::cout << "---PLAYER---\n";
	if (!name)std::cout << "NAME: NONE\n";
	else
		std::cout << "NAME: " << name << '\n';
	
	std::cout << "AGE: " << age << '\n'
		<< "WINS: " << wins << '\n'
		<< "POINTS: " << points << '\n'
		<< "GAMES PLAYED: " << gamesPlayed << '\n'
		<< "COEF OF WINS: " << CW << '\n';
}

void Player::print() const
{
	std::cout << name;
	std::cout << std::setw(5) << "\t" << wins << "\t" << std::setprecision(2) << CW << '\n';;
}

Player& Player::operator=(const Player& other)
{
	if (this != &other) 
	{
		age = other.age;				
		wins = other.wins;
		points = other.points;
		gamesPlayed = other.gamesPlayed;
		CW = other.CW;

		delete[] name;
		setName(other.name);
	}

	return *this;
}

size_t Player::spaceCount(const char* name) const
{
	int counter = 0;
	for (size_t i = 0; i < strlen(name); ++i)
	{
		if (name[i] == ' ') ++counter;
	}
	return counter;
}

bool Player::isValidSpace(const char* name) const
{
	return spaceCount(name) == 1 && strlen(name) >= 3 && name[0] != ' ' && name[strlen(name) - 1] != ' ';
}

std::istream& Player::read(std::istream& in)
{
	delete[] name;
	int size;
	in >> size; //takes first number that i dont need

	char* temp = new char[size + 1];
	in.getline(temp, size + 1);
	temp[size]='\0';
	setName(temp);
	
	int wins;
	in >> wins;
	setWins(wins);

	double coef;
	in >> coef;
	setCW(coef);

	return in;
}


std::ostream& Player::write(std::ostream& out) const
{
	out << strlen(name) << name << '\n' << wins << '\n' << CW;
	return out;
}

Player::Player():age(0), wins(0), points(0), gamesPlayed(0), name(nullptr)
{
}

Player::Player(size_t age, const char* name)
{
	setAge(age);
	setName(name);
}

Player::Player(size_t age, size_t wins, double coef, const char* name)
{
	setAge(age);
	setWins(wins);
	setCW(coef);
	setName(name);
}

Player::~Player()
{
	delete[] name;
}

std::istream& operator>>(std::istream& in, Player& p)
{
	p.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Player& p)
{
	p.write(out);
	return out;
}
