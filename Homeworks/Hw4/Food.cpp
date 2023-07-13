// File:    Food.cpp
// Purpose: Implementation file for the Food class.
//Gris Tran Hw4

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "Food.h"
using namespace std;

// CONSTRUCTOR

//Default constructor
Food::Food(int cooktime, const string &fname){
	Fname = fname;
	Cooktime = cooktime;
}

// ACCESSORS

//getName return the name of the food
const string Food::getName() const{
	return Fname;
}

//getCtine return the time remains to cook the food
int Food::getCtime() const{
	return Cooktime;
}

// A HELPER FUNCTION TO PRINT FOOD
void Food::printFood(){
	cout<<setw(2)<<left<<"";
	cout<<Fname<<" ("<<Cooktime<<" minute(s) left)"<<endl;
}

void Food::printCfood(){
	cout<<setw(2)<<left<<"";
	cout<<Fname<<endl;
}

// MODIFIERS

//Pass the cook time by 1 minute
void Food::ftime_pass(){
	//If cooktime already 0, it remain zero
	if(Cooktime <= 0){
		return;
	}
	Cooktime -= 1;
	
}


// A HELPER FUNCTION TO OOMPARE FOOD VALUE

//Compare the food value by smallest remaining cook time, with ties being broken by which name comes first
//alphabetically.
bool sortfood(const Food &f1, const Food &f2){
	int t1 = f1.getCtime();
	int t2 = f2.getCtime();
	string n1 = f1.getName();
	string n2 = f2.getName();
	if( t1 < t2){
		return true;
	}
	else if(t1 > t2){
		return false;
	}
	else if(n1 < n2){
		return true;
	}
	else if(n1 > n2){
		return false;
	}
	return false;
}
















































