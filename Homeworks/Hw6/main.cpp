//Gris Tran
//Homework 6 Star Battle Puzzle
// This program will take in an input file for a star battle puzzle
// and find solution for it by a recursion function

#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include "point.h"
using namespace std;

//GLOBAL VARIABLE---------------------------------------------------------------------------------------------------------------
//I KNOW THIS IS BAD BUT I DONT WANT TO HAVE TO MANY ARGUEMENTS IN MY FUCTION =((((
//I GUESS THERE IS A BETTER WAY, PLS EDUCATE ME IF THERE IS, THANK YOU SO MUCH!
typedef vector<vector<Point> >  vpp ;
typedef vector<Point> vp;
typedef vector<vector<int> > vvi;
typedef vector<vector<vector<int> > > vvvi;
typedef unsigned int uint;

int star;                                      //The maximum number of stars allowed in every zone, col and row.
int solutions = 0;                             //The number of total solution
vector<vector<vector<int> > > total_solution;  //This vector is used to store the valid solve of solution
vector<vector<Point> > block_position;		   //This vector is use to store the block in the puzzle, not fill = 0, filled = 1.
vector<vector<int> > board;                    //This board is use to store the block in the puzzle, not fill = 0, filled = 1. 
vector<vector<string> > puzzle;                //This vector is use to store the block by its zone symble
vector<string> zones;                          //This vector is use to store the zone symbol in the puzzle
bool find_one = false;                         //This boolen value is use to let the computer know that we only want to find 1 solution


//Zone Compare funtion 
//This function is use to help to sort the zone by the number of blocks in it
bool zone_compare(const vector<Point> &p1, const vector<Point> &p2){
	if(p1.size() < p2.size()){
		return true;
	}
	else if(p1.size() > p2.size()){
		return false;
	}
	return false;
}

//Check Point Next function
//This function is used to check if a Point p is next to a Point p1
bool check_point_next(Point p1, Point p2){
	int x1 = p1.getX();
	int y1 = p1.getY();
	int x2 = p2.getX();
	int y2 = p2.getY();
	if( pow(y1-y2,2) + pow(x1-x2, 2) <= 2 ) return false;
	return true;
}

//Check Next funtion
//This function is used to check if a Point p is next to any point p in a vector<point>
bool check_next(vector<int> index, vp &points, int k){
	Point p2 = points[k];
	for(uint i = 1; i<index.size(); i++){
		if(index[i] == -1) continue;
		if(check_point_next(points[index[i]],p2)) continue;
		return false;
	}
	return true;
}

//Convert function
//This function is used to convert a vector int of index in to a vector point
//of point equal 2 vp points[index]
vp convert(vector<int> id, vp points){
	vp newp;
	for(uint i = 1; i<id.size(); i++){
		newp.push_back(points[id[i]]);
	}
	return newp;
}

//Get Group Of Indicate function
//This function is used to get a group of point of number star and every point in this group is 
//checked to not be next to each other
void getGroupOfIndicate(vpp &res, vp &points, vector<int> &id, int start){
	if(start == star+1){
		vp newp = convert(id, points);
		res.push_back(newp);
		return;
	}
	for(uint k = id[start-1]+1; k < points.size(); k++){
		if(check_next(id, points, k)){
			id[start] = k;
			getGroupOfIndicate(res, points, id, start+1);
			id[start] = -1;
		}
	}
	return;
}

//Get Indicate By Zone funtion
//This function is use to create a vector<vector<Point>> 
vpp getIndicateByZone(const int index){
	vpp res;
	vp points = block_position[index];
	vector<int> indicate_point(star+1,-1);
	getGroupOfIndicate(res, points, indicate_point, 1);	
	return res;
}

//Check Horizontally Function
//This fuction is used to check and make sure that every row have exactly "star" stars.
bool checkHorizontally(int &y){
	int sum = 0;
	for(uint i = 0; i<board[y].size(); i++){
		if(board[y][i] == star){
			sum++;
		}
	}
	if(sum < star){
		return true;
	}
	return false;
}

//Check Vertically Function
//This fuction is used to check and make sure that every col have exactly "star" stars.
bool checkVertically(int &x){
	int sum = 0;
	for(uint i = 0; i<board.size(); i++){
		if(board[i][x] == star){
			sum++;
		}
	}
	if(sum < star){ 
		return true;
	}
	return false;
}

//Check Around Function
//This function is used to make sure that no point in the board stand next to each other
bool checkAround(Point &p){
	uint x = p.getX();
	uint y = p.getY();
	int sum = 0;
	sum += board[y][x];
	if( x >= 1) sum += board[y][x-1];
	if( x < board[y].size() - 1 ) sum += board[y][x+1];
	if( y >= 1) sum += board[y-1][x];
	if( y < board.size() - 1 ) sum += board[y+1][x];
	if( x >= 1 && y >= 1) sum += board[y-1][x-1];
	if( (x < board[y].size() - 1) && (y < board.size() - 1) ) sum += board[y+1][x+1];
	if( (y < board.size() - 1) && (x >= 1) ) sum += board[y+1][x- 1];
	if( (y >= 1) && (x < board[y].size() - 1) ) sum += board[y-1][x+1];
	if(sum != 0){
		return false;
	}
	return true;
}

//Point Is Valid function
//This function is used to check if that point p is hori, verti, around valid
bool PointIsValid(Point &p){
	int x = p.getX();
	int y = p.getY();
	if(!checkHorizontally(y)){
		return false;
	} 
	if(!checkVertically(x)){
		return false;
	}
	if(!checkAround(p)){
		return false;
	}
	return true;
}

//Indicate Is Valid funtion
//This function is used to check if every point in the choosen indicate list is valid
bool IndicateIsValid(vp &indi){
	vvi check_board = board;
	for(uint i = 0; i<indi.size(); i++){
		if(!PointIsValid(indi[i])) return false;
		
	}
	return true;
}

//Add Star To Board function
//This function is used to add the choosen point to fill a star in the board vector
//which is turn those points from 0 -> 1
void AddStarToBoard(vp &points){
	for(uint i = 0; i<points.size(); i++){
		board[points[i].getY()][points[i].getX()] = 1;
	}
	return;
}

//Remove Star From Board function
//This function is used to remove the choosen star in the board vector
//which is turn those points from 1 -> 0
void RemoveStarFromBoard(vp &points){
	for(uint i = 0; i<points.size(); i++){
		board[points[i].getY()][points[i].getX()] = 0;
	}
	return;
}

//Check All Board function
//This function is use to check the board when all of the zones have been filled s star
//If this check go through, the board will be count as a solution
bool check_all_board(){
	//Check col again
	for( uint i = 0; i<board.size(); i++){
		int sum1 = 0;
		for(uint j = 0; j<board[i].size(); j++){
			sum1 += board[i][j];
		}
		if(sum1 > star){
			return false;
		} 
	}
	//Check row again
	for( uint j = 0; j<board[0].size(); j++){
		int sum2 = 0;
		for( uint i = 0; i<board.size(); i++){
			sum2 += board[i][j];
		}
		if(sum2 > star) return false;
	}
	return true;
}


//Solve function
//This recurssion function will find the total valid solutions to solve the given puzzle
void solve(int index){
	//If find_one is changed to true, that means that we only want to find 1 solution.
	if(find_one && solutions == 1) return;
	if(index == zones.size()){
		if(check_all_board()){
			solutions++;
			total_solution.push_back(board);
		}
		return;
	}
	vpp indicates = getIndicateByZone(index);
	for(uint i = 0; i<indicates.size(); i++){
		vector<Point> p = indicates[i];
		if(IndicateIsValid(p)){
			AddStarToBoard(p);
			solve(index+1);
			RemoveStarFromBoard(p);
		}
	}	
}

//write_board function
//This function is used to support the write_all_solution function to write the puzzle board out
void write_board(vvi &boards, ofstream &outfile){
	for(uint i = 0; i< boards.size(); i++){
		for(uint j = 0; j<boards[i].size(); j++){
			if(boards[i][j] == 1){
				outfile<<"@";
			}
			else{
				outfile<<puzzle[i][j];
			}
		}
		outfile<<endl;
	}
	return;
}


//write_all_solution funtion
//This function is used to write all the solution in the output file
void write_all_solution( vvvi &solution, ofstream &outfile){
	outfile<<"Number of solutions: "<<solutions<<endl;
	outfile<<endl;
	for(uint i = 0; i<solution.size(); i++){
		outfile<<"Solution "<<i+1<<":"<<endl;
		write_board(solution[i], outfile);
		outfile<<endl;
	}
	return;
}

//write_one_solution funtion
//This function is used to write only one solution in the output file
void write_one_solution( vvvi &solution, ofstream &outfile){
	outfile<<"Number of solutions: 1"<<endl;
	outfile<<endl;
	write_board(solution[0], outfile);
	return;
}

//Check interesting case funtion----------------------------------------------------------------------------
//This function will check the intersting test case that:

// 1. If there is a zone have less or equal blocks than the num of required star and star > 1 => no solution (equal is wrong 2 since no block
//can be next to each other).
bool check_case1(){
	if(block_position[0].size() <= star && star>1) return false;  //check the smallest one, if smalles pass then all of the zone pass
	return true;
}

// 2. If the area of the puzzle is less than or equal to the num of required star => no solution
bool check_case2(int row, int col){
	if(row * col <= star) return false;
	return true;
}
// 3. If the number of columns or row < star and the number of zone >= star => no solution
//No matter how big the other row or columns is
bool check_case3(int row, int col){
	if(row < star && zones.size() >= star) return false;
	if(col < star && zones.size() >= star) return false;
	return true;
}

bool interesting_case(int row, int col){
	return check_case1() && check_case2(row, col) && check_case3(row, col);
}



//MAIN FUNCTION---------------------------------------------------------------------------------------------
int main(int argc, char* argv[] ) {	
	//Declare Variables for the first 3 arguements
	string required_star = argv[3];
	star = atoi(required_star.c_str());
	int row;
	int col;
	
	//Variable that help process the input file
  	vector<string> str;
  	string line;
  	string out_mode;
	
	//Open and read and process the input file into puzzle, block_position and zone vector.
	ifstream infile;
	infile.open(argv[1]);
	if (!infile) {
    	cerr << "Error: file could not be opened" << endl;
		exit(1); //Exit if file is open successfully
  	}
  	while ((infile>>line)) str.push_back(line);
  	infile.close();
  	
	//Set row and col
	row = atoi(str[0].c_str());
    col = atoi(str[1].c_str());
    
    //Fill in vector board
    for(int i = 0; i<row; i++){
		vector<int> num(col,0);
		board.push_back(num);
	}
    
    //Create the space for the puzzle vector
    for(int i = 0; i<row; i++){
    	vector<string> lines(col,"");
    	puzzle.push_back(lines);
	}
	
	//Process to fill in the vector block_position and zones
	//Start from the second line in the input file <=> i = 2
	for(uint i = 2; i< str.size()-3; ){
    	string zone_symbol = str[i];
    	zones.push_back(str[i]);
    	int blocks = atoi(str[i+1].c_str());
    	vector<Point> position;
    	for(int j = 0; j< blocks; j++){
    		int x = atoi(str[i+2].c_str());
    		int y = atoi(str[i+3].c_str());
    		position.push_back(Point(x,y,zone_symbol));
    		i+=2;
		}
		block_position.push_back(position);
		i+=2;
	}
	
	//Fill in vector puzzle
	for(uint i = 0; i<block_position.size(); i++){
		for(uint j = 0; j<block_position[i].size(); j++){
			puzzle[block_position[i][j].getY()][block_position[i][j].getX()] = zones[i];
		}
	}
	
	//Sort the vector block_position from the smallest zone to the largesr
	sort(block_position.begin(), block_position.end(), zone_compare);
	
	//Setting up an interesting test case
	//This test case is to test if there is a zone that have less blocks then the required star or 
	//The number of columns or row is lesser than the required number of star then there is no solution
	//for 100%
	bool interesting_condition = false;
	if(interesting_case(row, col)) interesting_condition = true;
	
	//Open the outfile and start to process
	ofstream outfile;
	
	//If the interesting case are not pass => no solution
	if(!interesting_condition){
		string outfilename = argv[2];
		outfile.open(outfilename.c_str());
		outfile<<"Number of solutions: 0";
		outfile.close();
	}
	
	//Else if interesting test cases are passed
	else if(argc == 6 && interesting_condition){
		out_mode = string(argv[4]);
		string solve_mode = string(argv[5]);
		
		//If output mode is one
		if(out_mode == "print" && solve_mode == "all_solutions"){
			solve(0);
			string outfilename = argv[2];
			outfile.open(outfilename.c_str());
			write_all_solution(total_solution, outfile);
			outfile.close();
		}
		else if(out_mode == "print" && solve_mode == "one_solution"){
			find_one = true;  //Let the program know that we only need 1 solution
			solve(0);
			if(solutions == 0){
				string outfilename = argv[2];
				outfile.open(outfilename.c_str());
				outfile<<"Number of solutions: 0";
				outfile.close();
			}
			else if(solutions > 0){
				string outfilename = argv[2];
				outfile.open(outfilename.c_str());
				write_one_solution(total_solution, outfile);
				outfile.close();
			}
		}
		else if(out_mode == "count" && solve_mode == "all_solutions"){
			solve(0);
			string outfilename = argv[2];
			outfile.open(outfilename.c_str());
			outfile<<"Number of solutions: "<<solutions;
			outfile.close();
		}
		else if(out_mode == "count" && solve_mode == "one_solution"){
			find_one = true;
			solve(0);
			if(solutions == 0){
				string outfilename = argv[2];
				outfile.open(outfilename.c_str());
				outfile<<"Number of solutions: 0";
				outfile.close();
			}
			else if(solutions > 0){
				string outfilename = argv[2];
				outfile.open(outfilename.c_str());
				outfile<<"Number of solutions: "<<solutions;
				outfile.close();
			}
		}
	}
	
	return 0;
}









