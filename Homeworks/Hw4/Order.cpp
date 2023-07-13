// File:    Order.cpp
// Purpose: Implementation file for the Order class.
//Gris Tran Hw4

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "Order.h"
using namespace std;


// CONSTRUCTOR

//Default constructor
Order::Order(int id, int time, int size, list<string> &name){
	Id =id;
	Time = time;
	Order_size = size;
	ls itr1;
	for(itr1 = name.begin(); itr1 != name.end(); itr1++){
		Name.push_back(*itr1);
	}
}

// ACCESSORS

//getId return the id of the order
int Order::getId() const{
	return Id;
}

//getTime return the time remain after expire of the order
int Order::getTime() const{
	return Time;
}

//getSize return the size of the order
int Order::getSize(){
	return Order_size;
}

//getItem return the list of item of the order
list<string> Order::getItems() const{
	return Name;
}

// MODIFIERS

//Pass the order by 1 minute
void Order::time_pass(){
	//If the order time is already 0, it remains 0
	if(Time <= 0){
		return;
	}
	Time -= 1;
}

// A HELPER FUNCTION TO PRINT A ORDER
void Order::printOrder(){
	cout<<"  #"<<Id;
	cout<<" ("<<Time<<" minute(s) left):"<<endl;
	for(ls itr1 = Name.begin(); itr1 != Name.end(); itr1++){
		cout<<setw(4)<<left<<"";
		cout<<*itr1<<endl;
	}
}

// A HELPER FUNCTION TO OOMPARE ORDER VALUE
//Compare the Order value by shortest time remaining, with
//ties resolved by order ID
bool sorttime(const Order &od1, const Order &od2){
	int t1 = od1.getTime();
	int t2 = od2.getTime();
	int id1 = od1.getId();
	int id2 = od2.getId();
	if(t1 < t2){
		return true;
	}
	else if(t1 > t2){
		return false;
	}
	else if(id1 < id2){
		return true;
	}
	else if(id1 > id2){
		return false;
	}
	return false;
}

bool sortid(const Order &od1, const Order &od2){
	int id1 = od1.getId();
	int id2 = od2.getId();
	if(id1 < id2){
		return true;
	}
	else if(id1 > id2){
		return false;
	}
	return false;
}
























