// File: Board.h
//Purpose: Header file with declaration of the Board class, including
//   member functions and private member variables.
//Gris Tran Hw3

#ifndef Board_h_
#define Board_h_

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Board{

public:
	// CONSTRUCTOR
	Board();
	Board(const string &p1, const string &p2, const string &blank);
	Board& operator=(const Board &br);
	~Board();  //Destructor
	
	// ACCESSORS
	int numRows() const;                //Get the number of rows
	int numColumns() const;			   	//Get the number of columns	
	int numTokensInRow(int rownum);     //Get the num of token in that row
	int numTokensInColumn(int colnum);	//Get the num of token in that column
	
	// A HELPER FUNCTION TO PRINT A BOARD
	friend ostream& operator<<(ostream &os, const Board &b);
	
	
	// MODIFIERS
	void clear();                              //Return the board to the initial condition
	string insert(int colnum, bool define);	   //Insert the token choosen in the column and check if there is a winner or not	 
	
private:
	// REPRESENTATION
	string P1;          //Player 1 string
	string P2;          //Player 2 string
	string Blank;       //The blank string
	string **m_data;    //The 2d pointer for the board
	int row;            //The num of row (initial will be 5)
	int col;            //The num of column (initial will be 4)
	int *height;        //The height of each column
	
	// PRIVATE MEMBER FUNCTIONS
	void copy(const Board &br);  //Copy Function
	void create();               //Create Function
	void create(const string &p1, const string &p2, const string &blank);
	
};

#endif
