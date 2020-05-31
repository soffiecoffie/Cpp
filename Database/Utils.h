﻿#ifndef UTILS__H
#define UTILS__H
#include <fstream>
#include <string>

//Полезни функции

int digits(int);
bool isOdd(int);
std::ostream& printMany(const char*, size_t, std::ostream&);
bool isSpaceBetweenWords(std::string, size_t);
std::string getWord(size_t, const std::string&);
size_t numOfWords(std::string);


#endif 