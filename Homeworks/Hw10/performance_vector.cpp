#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// defined in performance.cpp
void usage();


template <class T>
void vector_sort(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = vec.size();
  for (int i = 0; i < output_count; i++)
    ostr << vec[i] << "\n";
}


template <class T>
void vector_remove_duplicates(const std::vector<T> &vec, std::ostream &ostr, int &output_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    bool dup = false;
    for (int j = 0; j < i; j++) {
      if (vec[i] == vec[j]) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << vec[i] << "\n";
      output_count++;
    }
  }
}


template <class T>
void vector_mode(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::vector<T>::iterator current = vec.begin();
  ++current;
  typename std::vector<T>::iterator previous = vec.begin();
  for (; current != vec.end(); ++current, ++previous) {
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


// note: closest_pair is only available for integer data (not string data)
void vector_closest_pair(std::vector<int> &vec, std::ostream &ostr, int &output_count) {
  assert (vec.size() >= 2);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = 2;
  int best;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  for (unsigned int i = 0; i < vec.size()-1; i++) {
    int diff = vec[i+1]-vec[i];
    if (best_index == -1 || diff < best) {
      best = diff;
      best_index = i;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << vec[best_index] << "\n";
  ostr << vec[best_index+1] << "\n";
}


template <class T>
void vector_first_sorted(std::vector<T> &vec, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)vec.size() >= optional_arg);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = optional_arg;
  for (int i = 0; i < output_count; i++) {
    ostr << vec[i] << "\n";
  }
}


// note: longest_substring is only available for string data (not integer data)
//Helper Function
int min(int n1, int n2){
	if(n1 < n2) return n1;
	return n2;
}

string helper_function(unsigned int i, unsigned int j, string str1, string str2, vector<vector<string > > &dp){
	if(i >= str1.size() || j >= str2.size()) return "";
	if(dp[i][j] != "") return dp[i][j];
	string res1 = helper_function(i+1, j, str1, str2, dp);
	string res2 = helper_function(i, j+1, str1, str2, dp);
	string res3 = "";
	if(str1[i] == str2[j]){
		res3 = helper_function(i+1, j+1, str1, str2, dp);
		int index = 0;
		int check = 1;
		int size_ = res3.size();
		for(int k = i+1; k <= min(size_ + i, str1.size() - 1); k++){
			if(check == 0) break;
			if(res3[index] != str1[k]) check = 0;
			index++;
		}
		index = 0;
		for(int k = j+1; k <= min(size_ + j, str2.size() - 1); k++){
			if(check == 0) break;
			if(res3[index] != str2[k]) check = 0;
			index++;
		}
		if(check == 1) res3 = str1[i] + res3;
	}
	string ans[3] = {res1, res2, res3};
	string best_value = "";
	for(int k = 0; k<3; k++){
		if(ans[k].size() > best_value.size()) best_value = ans[k];
	}
	dp[i][j] = best_value;
	return best_value;
}

void vector_longest_substring(std::vector<std::string> &vec, std::ostream &ostr, int &output_count) {
	if(vec.empty()) return;
	int size_ = vec.size();
	string best_sub = "";
	output_count = 1;
  	for(int i = 0; i<size_; i++){
  		for(int j = i+1; j<size_; j++){
  			string str1 = vec[i];
			string str2 = vec[j];
			unsigned int n1 = str1.size();
			unsigned int n2 = str2.size();
			vector<vector<string> > dp(n1+1, vector<string>(n2+1,""));
			string temp = helper_function(0, 0, str1, str2, dp);
			if(temp.size() > best_sub.size()) best_sub = temp;
		}	
	}
	ostr<<best_sub<<endl;
}


void vector_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a vector of strings
    std::vector<std::string> vec;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      vec.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { vector_longest_substring (vec,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::vector<int> vec;
    int v;
    input_count = 0;
    while (istr >> v) {
      vec.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    else if (operation == "closest_pair")      { vector_closest_pair      (vec,ostr,output_count); }
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
