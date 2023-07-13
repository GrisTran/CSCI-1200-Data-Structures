#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
using namespace std;

// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  lst.sort();
  output_count = lst.size();
  typename list<T>::iterator itr;
  for(itr = lst.begin(); itr != lst.end(); itr++){
  	ostr << *itr << "\n";
  }
}

template <class T>
void list_remove_duplicates(std::list<T> &lst, std::ostream &ostr, int &output_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  typename list<T>::iterator i;
  typename list<T>::iterator j;
  for (i = lst.begin(); i != lst.end(); i++) {
    bool dup = false;
    for (j = lst.begin(); j != i; j++) {
      if (*i == *j) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << *i << "\n";
      output_count++;
    }
  }
}

template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lst.begin();
  ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for (; current != lst.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}

void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
  assert (lst.size() >= 2);
  // use the list sort algorithm
  lst.sort();
  output_count = 2;
  int best = 0;
  // the two elements with closest value must be next to each other in sorted order
  typename std::list<int>::iterator i;
  typename std::list<int>::iterator j;
  typename std::list<int>::iterator end = lst.end();
  end--;
  typename std::list<int>::iterator ans = lst.begin();
  for (i = lst.begin(); i != end; i++) {
  	j = i;
  	j++;
    int diff = *j - *i;
    if (diff < best || (best == 0 && i == lst.begin())) {
      best = diff;
      ans = i;
    }
  }
  // print the two elements
  ostr << *ans << "\n";
  ostr << *(++ans) << "\n";
}

template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)lst.size() >= optional_arg);
  // use the vector sort algorithm
  lst.sort();
  output_count = optional_arg;
  typename std::list<T>::iterator itr = lst.begin();
  for (int i = 0; i < output_count; i++) {
    ostr << *itr << "\n";
    itr++;
  }
}

string findlongest_sub(string s1, string s2){
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

void list_longest_substring(std::list<string> &lst, std::ostream &ostr, int &output_count) {
	output_count = 1;
	string longest_sub = "";
	typename std::list<string>::iterator itr;
	typename std::list<string>::iterator itr2;
	typename std::list<string>::iterator end = lst.end();
	end--;
	for(itr = lst.begin(); itr != end; itr++){
		for(itr2 = itr; itr2 != lst.end(); itr2++){
			if(itr2 == itr) itr2++;
			string str1 = *itr;
			string str2 = *itr2;
			string ans = findlongest_sub(str1, str2);
			if(ans.size() > longest_sub.size()) longest_sub = ans;
		}
	}
	ostr<<longest_sub<<endl;
}

void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;
  if (type == "string") {
    // load the data into a vector of strings
    std::list<string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  //std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  //exit(0);
  }
}
