/* 
                                              NOT FINISHED!

*/


#ifndef MENU_H
#define MENU_H
//#include "Com.h"
#include <fstream>

class Menu
{
	int input;

	//for keepsake purposes:
	char* myFileName;							//memoryfilename memory.txt
	char* userFileName;

	//bool to leave the cycle
	bool isDone;
	
	//help functions
	friend char* copyDynamic(const char*);
	void saveHelper(const char*, const char*);
	bool isValid(int);

public:
	Menu();
	Menu(int);
//	Menu(int, const char*, const char*);

	void setInput(int);
	void setMyFileName(const char*); //projectFileName? systemFileName? 
	void setUserFileName(const char*);

	void choice();
	bool getIsDone() const;
	void printOptions() const;

	void open();
	void save();
	void saveAs();
	void close();								//open for writing with trunc and close;
	//void save(const char*, std::ifstream&);
	//void saveAs(const char*, std::ifstream&);
	
												
												//should i stop the program after close file or give option to open a new one
};

#endif
