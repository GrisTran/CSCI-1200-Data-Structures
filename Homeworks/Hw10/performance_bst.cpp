#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;


// defined in performance.cpp
void usage();

template <class T>
void bst_sort(std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  typename map<T, int>::iterator itr;
  for(itr = mp.begin(); itr != mp.end(); itr++){
  	for(int i = 0; i<itr->second; i++){
  		ostr<<itr->first<<endl;
		output_count++;	
	} 
  }
}

template <class T>
void bst_remove_duplicates(std::map<int, T> &mp, std::ostream &ostr, int &output_count) { 
  typename map<int, T>::iterator itr;
  typename map<int, T>::iterator itr2;
  for(itr = mp.begin(); itr != mp.end(); itr++){
  	ostr<<itr->second<<endl;
  	output_count++;
  	itr2 = itr;
  	itr2++;
  	for(; itr2 != mp.end(); ){
  		if(itr2->second == itr->second){
  			typename map<int, T>::iterator remove_dub = itr2;
  			itr2++;
  			mp.erase(remove_dub);
  			continue;
		}
		itr2++;	
	}
  }
}

template <class T>
void bst_mode(std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  if(mp.empty()) return;
  output_count = 1;
  typename map<T, int>::iterator itr;
  int best_count = 0;
  T best_element;
  for(itr = mp.begin(); itr != mp.end(); itr++){
  	if(itr->second > best_count){
  		best_element = itr->first;
  		best_count = itr->second;
	}
  }
  ostr<<best_element<<endl;
}

void bst_closest_pair(std::map<int, int> &mp, std::ostream &ostr, int &output_count) {
  assert (mp.size() >= 2);
  // use the vector sort algorithm
  typename map<int, int>::iterator curr;
  typename map<int, int>::iterator next;
  typename map<int, int>::iterator end = mp.end();
  end--;
  typename map<int, int>::iterator ans = mp.begin();
  output_count = 2;
  int best = 0;
  // the two elements with closest value must be next to each other in sorted order
  for(curr = mp.begin(); curr != end; curr++){
  	next = curr;
  	next++;
  	int diff = next->first - curr->first;
  	if (diff < best || (best == 0 && curr == mp.begin() )) {
      best = diff;
      ans = curr;
    }
  }
  // print the two elements
  ostr << ans->first << "\n";
  ostr << (++ans)->first << "\n";
}

//Chua lam
template <class T>
void bst_first_sorted(std::map<T, int> &mp, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  // use the vector sort algorithm
  output_count = optional_arg;
  typename std::map<T, int>::iterator itr = mp.begin();
  while(output_count){
  	for(int i = 0; i<itr->second; i++){
  		if(output_count == 0){
  			break;	
		}  
  		ostr<<itr->first<<endl;
  		output_count--;
	} 
	itr++;
  }
}

string findlongest_sub_map(string s1, string s2){
	string ans;
	string final_ans = "";
	for(unsigned int i = 0; i<s1.size(); i++){
		for(unsigned int j = 0; j<s2.size(); j++){
			if(s1[i] == s2[j]){
				ans.push_back(s1[i]);
				int index_first = i;
				index_first++;
				for(unsigned int k = j+1; k <s2.size(); k++){
					if(index_first >= s1.size()) break;
					if(s1[index_first] == s2[k]){
						ans.push_back(s2[k]);
						index_first++;
					}
					else{
						if(ans.size() > final_ans.size()){
							final_ans = ans;
						}
						ans = "";
						break;
					}
				}
				if(ans != ""){
					if(ans.size() > final_ans.size()){
						final_ans = ans;
					}
					ans = "";
				}
			}
		}
	}
	return final_ans;
}

void bst_longest_substring(std::map<string, int> &mp, std::ostream &ostr, int &output_count) {
	output_count = 1;
	string longest_sub = "";
	typename std::map<string, int>::iterator itr;
	typename std::map<string, int>::iterator itr2;
	typename std::map<string, int>::iterator end = mp.end();
	end--;
	for(itr = mp.begin(); itr != end; itr++){
		for(itr2 = itr; itr2 != mp.end(); itr2++){
			if(itr2 == itr) itr2++;
			string str1 = itr->first;
			string str2 = itr2->first;
			string ans = findlongest_sub_map(str1, str2);
			if(ans.size() > longest_sub.size()) longest_sub = ans;
		}
	}
	ostr<<longest_sub<<endl;
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  // std::map<std::string,int> mp;
  if (type == "string") {
  	if(operation == "remove_duplicates"){
  		map<int, string> dub_mp;
  		std::string s;
        input_count = 0;
  		while (istr >> s) {
	  		dub_mp[input_count] = s;
      		input_count++;
    	}	
    	bst_remove_duplicates (dub_mp,ostr,output_count);
	}
	else{
	  	input_count = 0;
	  	string s;
	    // load the data into a vector of strings
	    std::map<std::string, int> mp;
	    while (istr >> s) {
	      if(mp.find(s) != mp.end()){
	      	mp[s]++;
	      	continue;
		  }
		  mp[s] = 1;
	      input_count++;
	    }
	    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
	    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
	    // "closest_pair" not available for strings
	    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
	    else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	  }
	}
  else {
  	assert (type == "integer");
  	if(operation == "remove_duplicates"){
  		input_count = 0;
  		map<int, int> dub_mp;
  		int v;
        input_count = 0;
  		while (istr >> v) {
	  		dub_mp[input_count] = v;
      		input_count++;
    	}	
    	bst_remove_duplicates (dub_mp,ostr,output_count);
	}
	else{
		input_count = 0;
	    // load the data into a vector of integers
	    std::map<int, int> mp;
	    int v;
	    input_count = 0;
	    while (istr >> v) {
	      if(mp.find(v) != mp.end()){
	      	mp[v]++;
	      	continue;
		  }
		  mp[v] = 1;
	      input_count++;
	    }
	    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
	    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
	    else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
	    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
	    // "longest_substring" not available for integers
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
  }

  //std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  //exit(0);
}
