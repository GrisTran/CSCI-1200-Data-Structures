#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Test{
public:
	Test(const string &s);
	
	string ** getPoint();
	
	friend ostream& operator<<(ostream &os, const Test &t);
private:
	string **box;

	
};


