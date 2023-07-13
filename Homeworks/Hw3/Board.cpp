// File:    Board.cpp
// Purpose: Implementation file for the Board class.
//Gris Tran Hw3

#include <iostream>
#include <string>
#include <cstddef>
#include <cassert>
#include "Board.h"

// CONSTRUCTOR
Board::Board(){
	this->create(); 
}
Board::Board(const string &p1, const string &p2, const string &blank){
	this->create(p1, p2, blank);
}

Board::~Board(){ 
	delete [] height; 
	for(int i = 0; i<col; i++){
		delete [] m_data[i];
	}
	delete [] m_data;
}

// ACCESSORS

//Fuction to return number of row of the Board
int Board::numRows() const{
	return row;
}

//Fuction to return number of column of the Board
int Board::numColumns() const{
	return col;
}

//Fuction to count number of token in the row of the Board
int Board::numTokensInRow(int rownum){
	if(rownum>=row || rownum<0){
		return -1;
	}
	else{
		int count = 0;
		for(unsigned int i = 0; i<col; i++){
			if(m_data[i][rownum] != Blank){
				count += 1;
			}
		}
		return count;
	}
}

//Fuction to count number of token in the column of the Board
int Board::numTokensInColumn(int colnum){
	if(colnum>=col || colnum<0){
		return -1;
	} 
	else{
		int count = 0;
		for(unsigned int i = 0; i<row; i++){
			if(m_data[colnum][i] != Blank){
				count += 1;
			}
		}
		return count;
	}
}

// PRIVATE MEMBER FUNCTIONS

//Function to create the default Board value
void Board::create(){
	P1 = "";
	P2 = "";
	Blank = "";
	m_data = NULL;
	height = NULL;
	row = 0;
	col = 0;
	
}

//Function to create the Board value
void Board::create(const string &p1, const string &p2, const string &blank){
	P1 = p1;
	P2 = p2;
	Blank = blank;
	m_data = new string*[4];
	height = new int[4];
	row = 5;
	col = 4;
	for(unsigned int i = 0; i<col; i++){
		height[i] = 0;
	}
	for(unsigned int i = 0; i<col; i++){
		m_data[i] = new string[row];
	}	
	for(unsigned int i = 0; i<col; i++){
		for(unsigned int j = 0; j<row; j++){
			m_data[i][j] = blank;
		}
	}
}

//Function to copy the Board value
void Board::copy(const Board &br){
	//Copy the variables
	this->P1 = br.P1;
	this->P2 = br.P2;
	this->Blank = br.Blank;
	this->row = br.row;
	this->col = br.col;
	this->height = new int[this->col];
	this->m_data = new string*[this->col];
	for(int i = 0; i < this->col; i++){
		this->m_data[i] = new string[this->row]; 
	}
	
	//Copy the 2d pointers contains board
	for(int i = 0; i<this->col; i++){
		for(int j = 0; j<this->row; j++){
			this->m_data[i][j] = br.m_data[i][j];
		}
	}
	
	//Copy the height check pointer
	for(int i = 0; i<this->col; i++){
		this->height[i] = br.height[i];
	}
}

//The = operator for Board value
Board& Board::operator=(const Board &br){
	if(this != &br){
		delete [] height;
		if(m_data){
			delete [] m_data;
		}
		this->copy(br);
	}
	return *this;
}

// MODIFIERS

//This funtion will place the token of player 1 or 2 in the Board
//First: Check if the column or the row is valid to place a new token
//Second: Place the token
//Last: Check if there is a winner or not
string Board::insert(int colnum, bool define){
	
	// If a player tries to place a token in a positive column that doesn’t exist yet, 
	//the board will grow to the right to fit by creating a new pointer to resize.
	if(colnum+1 > col){
		int extend = colnum + 1;
		string **newboard;
		newboard = new string*[extend];
		for(unsigned int i = 0; i<extend; i++){
			newboard[i] = new string[row];
		}	
		for(unsigned int i = 0; i<col; i++){
			for(unsigned int j = 0; j<row; j++){
				newboard[i][j] = m_data[i][j];
			}
		}
		for(unsigned int i = 0; i<col; i++){
			delete [] m_data[i];
		}
		delete [] m_data;
		m_data = newboard;
			
		//Creating new height check
		int *newheight = new int[extend]; 
		for(int i = 0; i<col; i++){
			newheight[i] = height[i];
		}
		delete [] height;
		height = newheight;
	
		//fill in the remaining blank
		for(unsigned int j = col; j<extend; j++){
			height[j] = 0;
		}
		for(unsigned int i = col; i<extend; i++){
			for(unsigned int j = 0; j<row; j++){
				m_data[i][j] = Blank;
			}
		}
		col = extend;
	}
	
	// If a token is placed in a column that is already “full”, the board will simply 
	//grow larger, allowing the new token to be placed at the top of the column by creating a new pointer to resize.
	if(height[colnum] == row){
		int extend = row + 1;
		string **newboard2;
		newboard2 = new string*[col];
		for(unsigned int i = 0; i<col; i++){
			newboard2[i] = new string[extend];
		}
		for(unsigned int i = 0; i<col; i++){
			for(unsigned int j = 0; j<row; j++){
				newboard2[i][j] = m_data[i][j];
			}
		}
		for(unsigned int i = 0; i<col; i++){
			delete [] m_data[i];
		}
		delete [] m_data;
		m_data = newboard2;
		//fill in the remaining blank
		for(unsigned int i = 0; i<col; i++){
			for(unsigned int j = row; j<extend; j++){
				m_data[i][j] = Blank;
			}
		}
		row = extend;
	}
	
	//Check if whether its Player 1 or Player 2 to place the token
	if(define == true){
		int posi = height[colnum];
		m_data[colnum][posi] = P1;
		height[colnum] += 1;
	}
	else if(define == false){
		int posi = height[colnum];
		m_data[colnum][posi] = P2;
		height[colnum] += 1;
	}
	
	//Check if there is a winner or not
	for(int i = 0; i < col; i++){
		for(int j = 0; j < row; j++){
			if(i + 4 <= col && m_data[i][j] != Blank){
				int check_hor = 0;
				for(int u = i; u<i+3; u++){
					if(m_data[u][j] == m_data[u+1][j]){
						check_hor += 1;
					}
				}
				if(check_hor == 3){
					return m_data[i][j];
				}
			}
			if(j + 4 <= row && m_data[i][j] != Blank){
				int check_ver = 0;
				for(int u = j; u<j+3; u++){
					if(m_data[i][u] == m_data[i][u+1]){
						check_ver += 1;
					}
				}
				if(check_ver == 3){
					return m_data[i][j];
				}
			}
		}
	}
	return Blank;	
}

//This function return the board to the initial condition
void Board::clear(){
	for(unsigned int i = 0; i<col; i++){
			delete[] m_data[i];
	}
	delete [] m_data;
	delete [] height;
	create();
}

// A HELPER FUNCTION TO PRINT A BOARD (operator <<)
ostream& operator<<(ostream &os, const Board &b){
	for(int i = b.numRows() - 1; i>=0; i--){
		for(int j = 0; j<b.numColumns(); j++){
			if(j == 0){
				os<<b.m_data[j][i];
			}
			else{
				os<<" "<<b.m_data[j][i];
			}
		}
		os<<endl;
	}
	return os;
}






















