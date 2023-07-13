#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

//Homework1 
//Gris Tran
// This program will take in an input file, execute 1 of 3 command (replace, dilation or erosion) and then return an output file

//Replace function
//This function will replace the org char into the rep char
void replace(char org, char rep, vector<string> &veccop, vector<string> &vecrep){
	for(int i = 0; i<int(veccop.size()); i++){
		for(int j =0; j<int(veccop[i].size()); j++){
			if(veccop[i][j] == org){
				vecrep[i][j] = rep;
			}
		}
	}
}



//Dilate funtion
//This function will dilating the input file 
void dilation(char org, vector<string> &veccop, vector<string> &vecrep){
	for(int i = 0; i<int(veccop.size()); i++){
		for(int j = 0; j<int(veccop[i].size()); j++){
			if(veccop[i][j] == org){
				vecrep[i+1][j] = org;
				vecrep[i-1][j] = org;
				vecrep[i][j-1] = org;
				vecrep[i][j+1] = org;
//The idea here is that if any char in the input stand next to the org char, it will become org.
			}
		}
	}
}

//Erosion function
//This function will eros those inout letter and turn it into another letter.
//For this fuction I will pass the outter line to prevent the out of range of the vector
void erosion(char rep, vector<string> &veccop, vector<string> &vecrep){
	for(int i = 1; i<int(veccop.size())-1; i++){
		for(int j = 1; j<int(veccop[i].size())-1; j++){
			if(veccop[i][j] == '.'){
				vecrep[i+1][j] = rep;
				vecrep[i-1][j] = rep;
				vecrep[i][j-1] = rep;
				vecrep[i][j+1] = rep;
//The idea here is in order to prevent erosion, one char have to be surround by the 'X' or the org char, so if there is a '.', everything arround it will be change into the rep char
			}
		}	
	}
}

//Copy function
//This function will print the input file after being executed into the output file 
void copy(vector<string> &vecrep, ofstream &outfile){
	for(int i = 0; i<int(vecrep.size()); i++){
		outfile<<vecrep[i]<<endl;
	}
}

int main(int argc, char* argv[]){
	
	//Creating variables
	vector<string> cop;
	vector<string> reply;
//The idea of having 2 vector is that so I wont mess up if sthg change during the loop which affect the outcome.
	char org = string(argv[4])[0];
	ifstream infile;
	ofstream outfile;
	string line;
	string order = string(argv[3]);
	
	//Open the input file and copy the text into the copy vector
	infile.open(argv[1]);
	if( !infile ){ //File could not open
		cerr << "Error: file could not be opened" << endl;
		exit(1); //Exit if file is open successfully
	}
	while(infile >> line){ //Read the file
		cop.push_back(line);
		reply.push_back(line);
	}
	infile.close();
	
	//Open the output file, execute the order and write the input into the outfile
	outfile.open(argv[2]);
	
	if(order == "replace"){
		replace(org, string(argv[5])[0], cop, reply);
		copy(reply, outfile);
	}
	else if(order == "dilation"){
		dilation(org, cop, reply);
		copy(reply, outfile);
	}
	else if(order == "erosion"){
		erosion(string(argv[5])[0], cop, reply);
		copy(reply, outfile);
	}
	
	outfile.close();
	 
  	return 0;
  
}

