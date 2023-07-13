#ifndef point_h_
#define point_h_
#include <bits/stdc++.h>
using namespace std;

//Hw6 - Gris Tran
// POINT CLASS
//This class will store the Point value and function to called for the point object
//and will be use to store the index of the blocks inside the puzzle.

class Point {
public:
	//CONSTRUCTOR
  	Point(int x0, int y0, string Block) : x(x0), y(y0), block(Block) {}
  	
  	//ACESSOR
  	string getBlock() const{
		return block;  
	}
	int getX(){
		return x;
	}
	int getY(){
		return y;
	}
  	
  	//HELPER FUNCTION
  	void print_Point(){
  		cout<<"Symbol: "<<block<<endl;
  		cout<<x<<" and "<<y<<endl;
  	}
 	
private:
	//POINT VALUE
	int x;
	int y;
  	string block;	
};


#endif

