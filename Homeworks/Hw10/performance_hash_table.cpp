#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void hash_table_remove_duplicates(unordered_map<T,int> &ht, std::ostream &ostr, std::istream &istr, int &output_count, int &input_count) { 
  T input;
  while(istr>>input){
  	input_count++;
  	if(ht.find(input) == ht.end()){
  		output_count++;
  		ostr<<input<<endl;	
  		ht[input] = 1;
	}
	ht[input]++;
  }
}

template <class T>
void hash_table_mode(unordered_map<T, int> &ht, std::ostream &ostr, int &output_count) {
  if(ht.empty()) return;
  typename unordered_map<T, int>::iterator itr;
  output_count = 1;
  int best_count = 0;
  T best_element;
  for(itr = ht.begin(); itr != ht.end(); itr++){
  	if(itr->second > best_count){
  		best_element = itr->first;
  		best_count = itr->second;
	}
  }
  ostr<<best_element<<endl;
}


void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR 
  // std::unordered_map<std::string,int> ht;

  if (type == "string") {
  	if(operation == "remove_duplicates"){
  		unordered_map<string, int> ht;
  		hash_table_remove_duplicates (ht,ostr,istr,output_count,input_count);		
	}
	else{
	    // load the data into a vector of strings
	    unordered_map<string, int> ht;
	    std::string s;
	    input_count = 0;
	    while (istr >> s) {
	      if(ht.find(s) != ht.end()){
	      	ht[s]++;
	      	continue;
		  }
		  ht[s] = 1;
	      input_count++;
	    }
	    if      (operation == "sort")              { output_count = 0; }
	    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
	    // "closest_pair" not available for strings
	    else if (operation == "first_sorted")      { output_count = 0; }
	    else if (operation == "longest_substring") { output_count = 0; }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
  }
  else {
    assert (type == "integer");
    if(operation == "remove_duplicates"){
  		unordered_map<int, int> ht;
  		hash_table_remove_duplicates (ht,ostr,istr,output_count,input_count);		
	}
    else{
	    unordered_map<int, int> ht;
	    int v;
	    input_count = 0;
	    while (istr >> v) {
	      if(ht.find(v) != ht.end()){
	      	ht[v]++;
	      	continue;
		  }
		  ht[v] = 1;
	      input_count++;
	    }
	    if      (operation == "sort")              { output_count = 0; }
	    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
	    else if (operation == "closest_pair")      { output_count = 0; }
	    else if (operation == "first_sorted")      { output_count = 0; }
	    // "longest_substring" not available for integers
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
  }
  //std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  //exit(0);
}
