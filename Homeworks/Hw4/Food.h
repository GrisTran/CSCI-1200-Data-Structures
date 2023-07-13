// File: Order.h
//Purpose: Header file with declaration of the Food class, including
//   member functions and private member variables.
//Gris Tran Hw4

#ifndef Food_h_
#define Food_h_

#include <cassert>
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Food{
	
public:
	// CONSTRUCTOR
	Food(int time, const string &fname);	
	
	// ACCESSORS
	int getCtime() const;
	const string getName() const;
	
	// MODIFIERS
	void ftime_pass(); 
	
	// A HELPER FUNCTION TO PRINT FOOD
	void printFood();
	void printCfood();
	
	
private:
	int Cooktime;
	string Fname;	
	
};

// A HELPER FUNCTION TO OOMPARE FOOD VALUE
bool sortfood(const Food &f1, const Food &f2);


#endif
