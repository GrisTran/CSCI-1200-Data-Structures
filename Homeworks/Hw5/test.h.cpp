#ifndef test_h_
#define test_h_

//Hw6 - Gris Tran
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is unrolled linked list,
// but there is no dummy head node and the list is not circular. This 
//unrolled linked list is simply a double link list but each node can
//contains varies value.

#include <bits/stdc++.h>
#include <iostream>
#include <cassert>
using namespace std;

//Define the fixed value of num of elements store in each Node
const int NUM_ELEMENTS_PER_NODE = 6;

// ===================================================================
// NODE CLASS
//This class will store the node of the unroll linked list
template <class T>
class Node {
public:
	//CONSTRUCTOR && DESTRUCTOR
	Node() : next_(NULL), prev_(NULL), num_elements(0) {}
	Node(const T &value);
	~Node() { destroy_node(); }
	
	// REPRESENTATION
	Node<T>* next_;          //The pointer to the next value
  	Node<T>* prev_;          //The pointer to the previous value
	T elements_array[NUM_ELEMENTS_PER_NODE];       //The array of value in the node
	int num_elements;        //The number of real element in the array
	
	// ACCESSORS
	bool isFull();
	bool isEmpty();
	
	//MODUFIER
	void copy_node(const Node<T>* itr);
	void destroy_node();
};

// -----------------------------------------------------------------
// NODE CLASS IMPLEMENTATION
//CONSTRUCTOR

template <class T> 
Node<T>::Node(const T &value){
	next_ = NULL;
	prev_ = NULL;
	elements_array[0] = value;
	num_elements = 0;
}

// ACCESSORS

//return true if the array in the node is fullt filled, else return false
template <class T> 
bool Node<T>::isFull(){
	if(num_elements == NUM_ELEMENTS_PER_NODE){
		return true;
	}
	return false;
}

//return true if the array in the node is empty, else return false
template <class T> 
bool Node<T>::isEmpty(){
	if(num_elements == 0){
		return true;
	}
	return false;
}

//MODUFIER
template <class T> 
void Node<T>::copy_node(const Node<T>* itr){
	num_elements = itr->num_elements;
	for(int i = 0; i<num_elements; i++){
		elements_array[i] = itr->elements_array[i];
	}
}

template <class T> 
void Node<T>::destroy_node(){
	num_elements = 0;
	next_ = prev_ = NULL;
}

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// ===================================================================
// LIST ITERATOR
template <class T>
class list_iterator {
public:
	//CONSTRUCTOR
	list_iterator(Node<T>* p=NULL, T* q=NULL) : ptr_(p), etr_(q), index(0) {}
	
	//DEFFERENCING OPERATOR GIVE ACCESS TO THE VALUE IN THE NODE ARRAY
	T& operator*();  
	
	//INCREMENT AND DECREMENT OPERATOR
	list_iterator<T> operator++(int); // post-increment, e.g., iter++
	list_iterator<T>& operator++(); // pre-increment, e.g., ++iter
	list_iterator<T> operator--(int); // post-decrement, e.g., iter--
	list_iterator<T>& operator--(); // pre-decrement, e.g., --iter
    
    //THE UnrolledLL CLASS NEEDS ACCESS TO PRIVATE PTR_, ETR_ & INDEX VARIABLE
  	friend class UnrolledLL<T>;
  	
  	//ACCESSOR
  	int getIndex() { return index; }
  	
  	// COMPARION OPERATOR
 	bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  	bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }
  	
private:
	// REPRESENTATION
  	Node<T>* ptr_;    // ptr to node in the unrolled list
  	T* etr_;          // ptr to the value in the node array
	int index = 0;    // the index to follow the array
};

// -----------------------------------------------------------------
// LIST ITERATOR CLASS IMPLEMENTATION
//DEFFERENCING OPERATOR GIVE ACCESS TO THE VALUE IN THE NODE ARRAY

template <class T>
T& list_iterator<T>::operator*(){
	etr_ = ptr_->elements_array;
	return etr_[index];
}

//INCREMENT AND DECREMENT OPERATOR

//Operator ++
//If the index does not reach the max num of elements in the node array,
//ptr_ will remain to point to the same node, else, ptr_ will point to the
//next node and index will be revalue back to 0
template <class T>
list_iterator<T> list_iterator<T>::operator++(int) { 
	if(index < ptr_->num_elements-1){
		index++;
		list_iterator<T> temp(*this);
		return temp;
	}
	else{
		index = 0;
		list_iterator<T> temp(*this);
		ptr_ = ptr_->next_;	
		return temp;
	}
}

template <class T>
list_iterator<T>& list_iterator<T>::operator++() { 
	if(index < ptr_->num_elements-1){
		index++;
		return *this;
	}
	else{
		index = 0;
		ptr_ = ptr_->next_;	
		return *this;
	}
}

//Operator --
//If the index does not reach the first elements in the node array,
//ptr_ will remain to point to the same node, else, ptr_ will point to the
//previous node and index will be revalue back to (NUM_ELEMENTS_PER_NODE-1)
template <class T>
list_iterator<T> list_iterator<T>::operator--(int) { 
	if(index < ptr_->num_elements-1 && index > 0){
		index--;
		list_iterator<T> temp(*this);
		return temp;
	}
	else if(index == 0){
		index = ptr_->prev_->num_elements-1;
		list_iterator<T> temp(*this);
		ptr_ = ptr_->prev_;	
		return temp;
	}
}

template <class T>
list_iterator<T>& list_iterator<T>::operator--() { 
	if(index < ptr_->num_elements && index > 0){
		index--;
		return *this;
	}
	else if(index == 0){
		index = ptr_->prev_->num_elements-1;
		ptr_ = ptr_->prev_;	
		return *this;
	}
}

// ===================================================================
// UNROLLED LINKED LIST 
template <class T>
class UnrolledLL {
public:
	//CONSTRUCTOR, DECONSTRUCTOR, COPY CONSTRUCTOR && ASSIGNMENT OPERATOR
	UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
	UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
	UnrolledLL& operator= (const UnrolledLL<T>& old);
	~UnrolledLL() { destroy_list(); }
	
	typedef list_iterator<T> iterator;
	
	//ACCESSORS && MODIFIERS
	unsigned int size() const { return size_; }
	bool empty() const { return head_ == NULL; }
	void clear() { destroy_list(); }
	
	//READ AND WRITE ACCESS TO CONTENT
	const T& front() const { return head_->elements_array[0];  }
  	T& front() { return head_->elements_array[0]; }
  	const T& back() const { return tail_->elements_array[tail_->num_elements-1]; }
  	T& back() { return tail_->elements_array[tail_->num_elements-1]; }
	
	//MODIFY THE UNROLLED LINK LIST STRUCTOR
	void push_front(const T& v);
  	void pop_front();
  	void push_back(const T& v);
  	void pop_back();
  	
  	//ITERATOR FUNCTION TO ACCESS/MODIFY CONTENT IN THE LIST
  	iterator erase(iterator itr);
  	iterator insert(iterator itr, const T& v);
  	iterator begin() { return iterator(head_); }
  	iterator end() { return iterator(NULL); }
  	
  	//HELPER FUNCTION TO PRINT THE UROLLEDLL VALUE
  	void print(std::ostream& os);
  	
private:
  //PRIVATE HELPER FUNCTION
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;      //The pointer point to the first node
  Node<T>* tail_;      //The pointer point to the last node
  unsigned int size_;  //The num of the elements in the whole list
};
// -----------------------------------------------------------------
//----- UNROLLED LINKED LIST CLASS IMPLEMENTATION -----//

//ASSIGNMENT OPERATOR
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check if 2 list r the same or not
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

//MODIFY THE UNROLLED LINK LIST STRUCTOR
//Fuction push_front
//This fuction will added the v value to the front of the list
//There will be 3 cases: list was empty, list was not empty but array is not full && list is not empty and array is full
template <class T>
void UnrolledLL<T>::push_front(const T& v){
	//Case1: If list is empty we create and add a new node w value v in index 0 of the array
	if(head_ == NULL){
		head_ = new Node<T>(v);
		tail_ = head_;
	}
	//Case2: If array is not full we just add the v to the front of the array
	else if(!head_->isFull()){
		for(int i = head_->num_elements; i>0; i--){
			head_->elements_array[i] = head_->elements_array[i-1];
		}
		head_->elements_array[0] = v; 
	}
	//Case3: If array is full we create a new node w value v and add to the front of the list
	else if(head_->isFull()){
		Node<T>* newnode = new Node<T>(v);
		newnode->next_ = head_;
		head_->prev_ = newnode;
		head_ = newnode;
	}
	size_++;
	head_->num_elements++;
}

//pop_front function
//This function will pop the first element in the list
//There will be 3 cases: list is empty, list only have 1 elements, list have more than 1 elements(not node)
template <class T>
void UnrolledLL<T>::pop_front(){
	//Case1: List is empty => just return 
	if(size_ == 0){
		head_ = tail_ = NULL;
		return;
	}
	//Case2: List only have 1 elements => we can just delete this node and point head and tail to NULL
	else if(size_ == 1){
		Node<T>* deletenode = head_;
		head_ = tail_ = NULL;
		delete deletenode;
		size_--;
		return;
	}
	//Case3: List has more than 1 node => We just pop the first node in the array
	//However, we still have to check if we need to delete the node since there may
	//be node w 1 elements.
	else{
		for(int i = 0; i<head_->num_elements-1; i++){
			head_->elements_array[i] = head_->elements_array[i+1];
		}
		head_->num_elements--;
		size_--;
		//Check to see if we have to delete the node
		if(head_->num_elements == 0){
			Node<T>* deletenode = head_; 
			head_ = head_->next_;
			head_->prev_ = NULL;
			delete deletenode;
		}
	}
}

//push_back funtion
//This function will add value v to the back of the list
//There will be 3 cases: list is empty, node is not full and node is full
template <class T>
void UnrolledLL<T>::push_back(const T& v){
	//Case1: List is empty => add a new node
	if(tail_ == NULL){
		tail_ = new Node<T>(v);
		head_ = tail_;
	}
	//Case2: Array is not full => just add value v to the end of the array
	else if(!tail_->isFull()){
		tail_->elements_array[tail_->num_elements] = v;
	}
	//Case3: Array is full => add a new node w value v to the end of the list
	else if(tail_->isFull()){
		Node<T>* newnode = new Node<T>(v);
		newnode->prev_ = tail_;
		tail_->next_ = newnode;
		tail_ = newnode;
	}
	size_++;
	tail_->num_elements++;
}


//pop_back funtion
//This funtion will pop the last element in the list
//There will be 3 cases: List is empty, list only have 1 elements and list have more than 1 elements
template <class T>
void UnrolledLL<T>::pop_back(){
	//Case1: List is empty => just return 
	if(size_ == 0){
		head_ = tail_ = NULL;
		return;
	}
	//Case2: List only have 1 elements => we can just delete this node and point head and tail to NULL
	else if(size_ == 1){
		Node<T>* deletenode = tail_;
		head_ = tail_ = NULL;
		delete deletenode;
		size_--;
		return;
	}
	//Case3: List has more than 1 node => We just pop the last elements in the last node in the list
	//However, we still have to check if we need to delete the node since there may
	//be node w 1 elements.
	else{
		tail_->num_elements--;
		size_--;
		//Check to see if we have to delete the node
		if(tail_->num_elements == 0){
			Node<T>* deletenode = tail_; 
			tail_ = tail_->prev_;
			tail_->next_ = NULL;
			delete deletenode;
		}
	}
}

//ITERATOR FUNCTION TO ACCESS/MODIFY CONTENT IN THE LIST
//erase function 
//This funtion will erase the value that itr point to in the array in the node, there will be 2 case:
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr){
	assert (size_ > 0);
	size_--;
	//Case 1: if the size of the element in the value in the node = 1 => we can just delete the whole node
	//This case 1 will have 3 small cases
	if(itr.ptr_->num_elements == 1){
		iterator result(itr.ptr_->next_);
		//Scase1: there are only 1 node in the list
		if (itr.ptr_ == head_ && head_ == tail_) {
    		head_ = tail_ = 0;
  		}
  		//If the node is the first node of the list
		else if (itr.ptr_ == head_) {
    		head_ = head_->next_;
    		head_->prev_ = 0;
  		}	
  		//If the node is the last node of the list
		else if (itr.ptr_ == tail_) {
    		tail_ = tail_->prev_;
    		tail_->next_ = 0;
  		}	
  		//The list is either the first or last node of the list
  		//=> normal remove
  		else {
    		itr.ptr_->prev_->next_ = itr.ptr_->next_;
    		itr.ptr_->next_->prev_ = itr.ptr_->prev_;
  		}	
  		delete itr.ptr_;
  		return result;
	}
	//Case 2: If the size of the node in the array is larger than 1 => We dont have to delete the whole node.
	//We will just need no delete the pointed value in the array by moving every value by 1 start at the last value
	//and end at the pointed value. 
	//There will be a special case when the node pointed to be erase is the last node of the array. At this case, after
	//the normal process loop, we will just move to the next node immediately.
	else if(itr.ptr_->num_elements > 1){
		int oldindex = itr.getIndex();
		//If the index == number of elements - 1 => move to next node
		if(oldindex == itr.ptr_->num_elements-1){
			itr.ptr_->num_elements--;
			iterator result(itr.ptr_->next_);
			return result;
		}
		//Get the index of the value being erased
		for(int i = itr.getIndex(); i < itr.ptr_->num_elements-1; i++){
			itr.ptr_->elements_array[i] = itr.ptr_->elements_array[i+1];
		}
		itr.ptr_->num_elements--;
		return itr;
	}
}

//insert function 
//This funtion will insert the value v right before the value that itr point to in the array in the node, there will be 2 case:
//The node is full or the node is not full
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v){
	size_++;
	//Case 1: If the node is not full, we just need to move the value start from value pointed
	//by iterator itr to the right by 1 and add v into the prev position of itr
	if(!itr.ptr_->isFull()){
		int itr_index = itr.getIndex();
		for(int i = itr.ptr_->num_elements; i>itr_index; i--){
			itr.ptr_->elements_array[i] = itr.ptr_->elements_array[i-1];
		}
		itr.ptr_->elements_array[itr_index] = v;
		itr.ptr_->num_elements++;
		return itr;
	}
	//Case 2: If the node is full, we will need to move all of the value start from value pointed by
	//itr to the last value into a new node to prevent override. After that we add v into the prev 
	//position of itr and add the new node into the list.
	else if(itr.ptr_->isFull()){
		Node<T>* override_node = new Node<T>;
		int move_index = itr.getIndex();
		//get the new size of the new node
		int newnode_size = NUM_ELEMENTS_PER_NODE - move_index;
		for(int i = 0; i<newnode_size; i++){
			override_node->elements_array[i] = itr.ptr_-> elements_array[i+move_index];
		}
		itr.ptr_-> elements_array[move_index] = v;
		override_node->num_elements = newnode_size;
		itr.ptr_->num_elements -= newnode_size;
		itr.ptr_->num_elements++;
		override_node->prev_ = itr.ptr_;
		override_node->next_ = itr.ptr_->next_;
		itr.ptr_->next_ = override_node;
		//If ptr point to the last node
		if(itr.ptr_ == tail_){
			tail_ = override_node;
		}
		//Normal add
		else{
			override_node->next_->prev_ = override_node;
		}
		return itr;
	}
}

//HELPER FUNCTION TO PRINT THE UROLLEDLL VALUE
template <class T>
void UnrolledLL<T>::print(std::ostream& os){
	os<<"UnrolledLL, size: "<<size_;
	unsigned int i = 0;
	UnrolledLL<T>::iterator itr = head_;
	while(i<size_){
		if(itr.getIndex() == 0){
			cout<<endl<<" node:["<<itr.ptr_->num_elements<<"]";
		}
		os<<" "<<*itr;
		i++;
		itr++;
	}
	cout<<endl;
}

//PRIVATE HELPER FUNCTION
//copy_list funtion
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old){
	size_ = old.size_;
	if(size_ == 0){
		head_ = tail_ = 0;
    	return;
	}
	head_ = new Node<T>;
	head_->copy_node(old.head_);
	tail_ = head_;
	Node<T>* old_p = old.head_->next_;
	while(old_p){
		tail_->next_ = new Node<T>;
		tail_->next_->copy_node(old_p);
		tail_->next_->prev_ = tail_;
		tail_ = tail_->next_;
		old_p = old_p->next_;
	}	
}

//destroy_list function
template <class T>
void UnrolledLL<T>::destroy_list(){
	
	
	if(size_ == 0){
		head_= tail_ = NULL;
		return;
	}
	Node<T>* current = head_;
	Node<T>* next = NULL;
	while(current != NULL){
		next = current->next_;
		current->destroy_node();
		delete current;
		current = next;
	}
	head_ = NULL;
	tail_ = NULL;		
	size_ = 0;
}







#endif
