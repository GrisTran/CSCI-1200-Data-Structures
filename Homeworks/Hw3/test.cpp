#include <iostream>
#include <vector>
#include <string>
#include "test.h"
using namespace std;

Test::Test(const string &s){
	box =  new string*[4];
	for(int i = 0; i<4; i++){
		box[i] = new string[5];
	}
	for(int i = 0; i<4; i++){
		for(int j = 0; j<5; j++){
			box[i][j] = s;
		}
	}
}

string ** Test::getPoint(){
	return box;
}

ostream& operator<<(ostream &os, const Test &t){
	for(int i = 4; i>=0; i--){
		for(int j = 0; j<4; j++){
			os<<t.box[j][i]<<" ";
		}
		os<<endl;
	}
	return os;
}









