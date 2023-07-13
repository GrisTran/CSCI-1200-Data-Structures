// File: Order.h
//Purpose: Header file with declaration of the Order class, including
//   member functions and private member variables.
//Gris Tran Hw4

#ifndef Order_h_
#define Order_h_

#include <cassert>
#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef list<string>::iterator ls;

class Order{
	
public:
	// CONSTRUCTOR
	Order(int id, int time, int size, list<string> &name);
	
	// ACCESSORS
	int getId() const;
	int getTime() const;
	int getSize();
	list<string> getItems() const;
	
	// MODIFIERS
	void time_pass();
	
	// A HELPER FUNCTION TO PRINT A ORDER
	void printOrder();
		
private:
	//Value for order
	int Id;
	int Time;
	int Order_size;
	list<string> Name;
};

// A HELPER FUNCTION TO OOMPARE ORDER VALUE
bool sorttime(const Order &od1, const Order &od2);
bool sortid(const Order &od1, const Order &od2);




#endif
