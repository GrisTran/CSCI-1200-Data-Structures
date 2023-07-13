#include <iostream>
#include <list>
using namespace std;

class QUERY{
public:
	//CONSTRUCTOR
	QUERY();
	
		
		
private:
	string title;
	string year;
	string time;
	int genres;
	list<string> genres_list;
	int actor_code;
	list<string> actor_list;
	int role;
	list<string> role_list;	
};
