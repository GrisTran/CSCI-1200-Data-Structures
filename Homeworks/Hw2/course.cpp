// File:    course.cpp
// Purpose: Implementation file for the Course class.

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "course.h"
using namespace std;

// CONSTRUCTOR
Course::Course(vector<string> cvec){  //include a vector which have 8 stats
	CRN = atoi(cvec[0].c_str());
	Dcode = cvec[1];
	Ccode = cvec[2];
	Cname = cvec[3];
	Cday = cvec[4];
	Stime = cvec[5];
	Etime = cvec[6];
	Croom = cvec[7];
}

// ACCESSORS
string Course::getDay() const{
	return Cday;
}

string Course::getCname() const{
	return Cname;
}

string Course::getTime() const{
	return Stime;
}

string Course::getEtime() const{
	return Etime;
}

string Course::getCode() const{
	return Ccode;
}

string Course::getDcode() const{
	return Dcode;
}

string Course::getRoom() const{
	return Croom;
}

//Function to return value to weekday
int courseday(const Course &cd){
	string day = cd.getDay();
	if(day == "Monday"){
		return 1;
	}
	else if(day == "Tuesday"){
		return 2;
	}
	else if(day == "Wednesday"){
		return 3;
	}
	else if(day == "Thursday"){
		return 4;
	}
	else if(day == "Friday"){
		return 5;
	}
}

//Function to get the Am or Pm
char timestat(const Course &cr){
	string time = cr.getTime();
	char stat = time[5];
	int val = timevalue(cr);
	if(stat == 'P' && val == 12){
		return 'A';
	}
	return stat;
}

//Function to get the first 2 digit of the time
int timevalue(const Course &ct){
	string timee = ct.getTime();
	int val = atoi(timee.c_str());
	return val;
}
//Function to sort the Course value base on Weekday -> Time start -> Course code -> Dept name
bool compare_room(const Course &cr1, const Course &cr2){
	int wday1 = courseday(cr1);
	int wday2 = courseday(cr2);
	char stime1 = timestat(cr1);
	char stime2 = timestat(cr2);
	int vtime1 = timevalue(cr1);
	int vtime2 = timevalue(cr2);
	string ccode1 = cr1.getCode();
	string ccode2 = cr2.getCode();
	string dname1 = cr1.getDcode();
	string dname2 = cr2.getDcode();
	if(wday1 < wday2){
		return true;
	}
	else if(wday1 > wday2){
		return false;
	}
	if(stime1 == 'A' && stime2 == 'P'){
		return true;
	}
	else if(stime1 == 'P' && stime2 == 'A'){
		return false;
	}
	if(vtime1 < vtime2){
		return true;
	}
	else if(vtime1 > vtime2){
		return false;
	}
	if(ccode1 < ccode2){
		return true;
	}
	else if(ccode1 > ccode2){
		return false;
	}
	if(dname1 < dname2){
		return true;
	}
	else if(dname1 > dname2){
		return false;
	}
	return false;	
}

//Function to sort the Course value base on Course code -> Weekday -> Time start
bool compare_dept(const Course &cr1, const Course &cr2){
	string ccode1 = cr1.getCode();
	string ccode2 = cr2.getCode();
	int wday1 = courseday(cr1);
	int wday2 = courseday(cr2);
	char stime1 = timestat(cr1);
	char stime2 = timestat(cr2);
	int vtime1 = timevalue(cr1);
	int vtime2 = timevalue(cr2);
	if(ccode1 < ccode2){
		return true;
	}
	else if(ccode1 > ccode2){
		return false;
	}
	if(wday1 < wday2){
		return true;
	}
	else if(wday1 > wday2){
		return false;
	}
	if(stime1 == 'P' && stime2 == 'A'){
		return true;
	}
	else if(stime1 == 'A' && stime2 == 'P'){
		return false;
	}
	if(vtime1 > vtime2){
		return true;
	}
	else if(vtime1 < vtime2){
		return false;
	}
	return false;	
}

//Function to sort the Course value base on Course code -> Time start -> Dept name
bool compare_custom(const Course &cr1, const Course &cr2){
	string ccode1 = cr1.getCode();
	string ccode2 = cr2.getCode();
	char stime1 = timestat(cr1);
	char stime2 = timestat(cr2);
	int vtime1 = timevalue(cr1);
	int vtime2 = timevalue(cr2);
	string dname1 = cr1.getDcode();
	string dname2 = cr2.getDcode();
	if(ccode1 < ccode2){
		return true;
	}
	else if(ccode1 > ccode2){
		return false;
	}
	if(stime1 == 'A' && stime2 == 'P'){
		return true;
	}
	else if(stime1 == 'P' && stime2 == 'A'){
		return false;
	}
	if(vtime1 < vtime2){
		return true;
	}
	else if(vtime1 > vtime2){
		return false;
	}
	if(dname1 < dname2){
		return true;
	}
	else if(dname1 > dname2){
		return false;
	}
	return false;
}

//Funtion to print the Course value in room order
void Printcourse(int length, int length2, const Course &cr, ofstream &file){
	string dcode = cr.getDcode();
	string ccode = cr.getCode();
	string cname = cr.getCname();
	string day = cr.getDay();
	string stime = cr.getTime();
	string etime = cr.getEtime();	
	file<<setw(6)<< left << dcode;
	file<<setw(11)<< left << ccode;
	file<<setw(length)<< left << cname;
	file<<setw(length2)<< left << day;
	file<<setw(12)<< left << stime;
	file<<setw(8)<< left << etime << endl;
}

//Funtion to print the Course value in dept order
void Printdept(int length, int length2, const Course &cr, ofstream &file){
	string ccode = cr.getCode();
	string cname = cr.getCname();
	string day = cr.getDay();
	string stime = cr.getTime();
	string etime = cr.getEtime();	
	file<<setw(11)<< left << ccode;
	file<<setw(length)<< left << cname;
	file<<setw(length2)<< left << day;
	file<<setw(12)<< left << stime;
	file<<setw(8)<< left << etime << endl;
}

//Funtion to print the Course value in custom order
void Printcustom(int length, const Course &cr, ofstream &file){
	string dcode = cr.getDcode();
	string ccode = cr.getCode();
	string cname = cr.getCname();
	string stime = cr.getTime();
	string etime = cr.getEtime();
	file<<setw(6)<< left << dcode;	
	file<<setw(11)<< left << ccode;
	file<<setw(length)<< left << cname;
	file<<setw(12)<< left << stime;
	file<<setw(8)<< left << etime << endl;
}




	
	
	
	
	
	
	
	
	
	
	
	
	



