#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"
#include <stdlib.h> // for my student test

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){
	
	//Test if the insert function work right
	
	Board uni("RPI", "MIT", "***");
	std::string Result;
	std::cout<<endl;
	std::cout<<"This is the student test of Gris Tran"<<std::endl;
	std::cout<<"Initial Uni Board"<<std::endl;
	std::cout<< uni <<std::endl;
	bool condi = true;
	int round = 0;
	while(condi){
		int satscore = rand() % 250 + 1350; //Generate a random sat score from range 1400 - 1600
		cout<<satscore<<endl;
		if(satscore >= 1500){
			Result = uni.insert(1,false);
		}
		else{
			Result = uni.insert(2,true);
		}
		std::cout<<"Round "<<round<<":"<<std::endl;
		std::cout<< uni <<std::endl;
		if(Result != "***"){
			std::cout<<"I guess "<<Result<<" is the better school lol!"<<std::endl;
			condi = false;
		}
		else{
			std::cout<<"No result yet!"<<std::endl;
		}
		round++;
	}
	
	//Test the copy constructor
	Board uni_copy;
	uni_copy = uni;
	
	std::cout<<std::endl<<"This is the copy version of the uni board after clear() being called"<<std::endl;
	std::cout<<uni_copy<<endl;
	
	//Test the clear function
	uni.clear();
	
	//Make sure that the copy work and the copy Board value is not being affected by the clear
	std::cout<<"This is the copy version of the uni board before clear() being call"<<std::endl;
	std::cout<<uni_copy<<endl;
	




































}

