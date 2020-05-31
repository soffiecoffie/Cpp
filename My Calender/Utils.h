#ifndef UTILS_H
#define UTILS_H

#include <string>

//Полезни функции:

size_t getNumOfWords(std::string);
std::string getFistWord(std::string);
size_t getFirstSpaceInd(std::string);
std::string getWord(size_t, const std::string&);
std::string getStringAfterWord(size_t, const std::string&);



#endif 