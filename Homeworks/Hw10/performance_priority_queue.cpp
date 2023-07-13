#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > minpqueue;
typedef std::priority_queue<int,std::vector<int>, std::greater<int> > int_minpqueue;

// defined in performance.cpp
void usage();

//template <class T, class Container = vector<T>, class Compare = greater<T> >
template <class T>
void pqueue_sort(priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) {
  while(!pq.empty()){
  	output_count++;
  	ostr<<pq.top()<<endl;
  	pq.pop();
  }
}

template <class T>
void pqueue_mode(priority_queue<T, vector<T>, greater<T> > &pq, std::ostream &ostr, int &output_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  T max_value;
  output_count = 1;
  if(pq.empty()) return;
  T check = pq.top();
  max_value = check;
  int max = 0;
  int count = 1;
  
  while(!pq.empty()){
  	if(pq.top() == check){
  		if(count > 1) pq.pop();
		count++;	
	}
  	else{
		if(count > max){
			max = count;
			max_value = check;
		}
		check = pq.top();
		pq.pop();
		count = 1;
	}
	if(pq.size() == 1){
		pq.pop();
		if(count > max){
			max = count;
			max_value = check;
		}	
	}
  }
  ostr<<max_value<<endl;
}

void pqueue_closest_pair(int_minpqueue &pq, std::ostream &ostr, int &output_count) {
  assert (pq.size() >= 2);
  output_count = 2;
  int best = 0;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  int_minpqueue copy_pq = pq;
  int index = -1;
  while(!pq.empty()){
  	int curr = pq.top();
  	pq.pop();
  	index++;
  	if(pq.empty()) continue;
  	int next = pq.top();
  	int diff = next - curr;
  	if(best_index == -1 || diff < best){
  		best = diff;
      	best_index = index;	
	}
  }
  while(best_index--){
  	copy_pq.pop();
  }
  // print the two elements
  output_count = 2;
  ostr << copy_pq.top() << "\n";
  copy_pq.pop();
  ostr << copy_pq.top() << "\n";
}

template <class T>
void pqueue_first_sorted(priority_queue<T, vector<T>, greater<T> > &pq, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)pq.size() >= optional_arg);
  output_count = optional_arg;
  for(int i = 0; i<output_count; i++){
  	ostr<<pq.top()<<endl;
  	pq.pop();
  }
}


void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {
	
  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)
  if (type == "string") {
    // load the data into a vector of strings
    minpqueue pq;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }
    if      (operation == "sort")              { pqueue_sort<string>             (pq, ostr, output_count); }
    else if (operation == "remove_duplicates") { output_count = 0; }
    else if (operation == "mode")              { pqueue_mode<string>            (pq,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { pqueue_first_sorted<string>      (pq,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { output_count = 0; }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    int_minpqueue pq;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }
    if      (operation == "sort")              { pqueue_sort<int>              (pq,ostr,output_count); }
    else if (operation == "remove_duplicates") { output_count = 0; }
    else if (operation == "mode")              { pqueue_mode<int>              (pq,ostr,output_count); }
    else if (operation == "closest_pair")      { pqueue_closest_pair     (pq,ostr,output_count); }
    else if (operation == "first_sorted")      { pqueue_first_sorted<int>      (pq,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  //std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  //exit(0);
  
}

