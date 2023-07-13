// File: course.h
//Purpose: Header file with declaration of the Course class, including
//   member functions and private member variables.

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Course{
	
public:
	// CONSTRUCTOR
	Course(vector<string> cvec);
	
	// ACCESSORS
	string getDay() const;
	string getTime() const;
	string getEtime() const;
	string getCode() const;
	string getDcode() const;
	string getCname() const;
	string getRoom() const;
	
private:
	int CRN;
	string Dcode;
	string Ccode;
	string Cname;
	string Cday;
	string Stime;
	string Etime;
	string Croom;
		
	
};

//Function to return value to weekday
int courseday(const Course &cd);

//Function to get the Am or Pm
char timestat(const Course &cr);

//Function to get the first 2 digit of the time
int timevalue(const Course &ct);

//Function to sort the Course value base on Weekday -> Time start -> Course code -> Dept name
bool compare_room(const Course &cr1, const Course &cr2);

//Function to sort the Course value base on Course code -> Weekday(lastest first) -> Time start
bool compare_dept(const Course &cr1, const Course &cr2);

//Function to sort the Course value base on Course code -> Time start -> Dept name
bool compare_custom(const Course &cr1, const Course &cr2);

//Funtion to print the Course value in room order
void Printcourse(int length, int length2, const Course &cr, ofstream &file);

//Funtion to print the Course value in dept order
void Printdept(int length, int length2, const Course &cr, ofstream &file);

//Funtion to print the Course value in custom order
void Printcustom(int length, const Course &cr, ofstream &file);










