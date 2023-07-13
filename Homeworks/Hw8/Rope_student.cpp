/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include <string>
#include <vector>
#include "Rope.h"
using namespace std;

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	if (ptr_->right != NULL) {
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) {
        ptr_ = ptr_->left;
      }
    } 
	else {
      	while (ptr_->parent && ptr_->parent->right == ptr_){
      		ptr_ = ptr_->parent;
	  	}
   		ptr_ = ptr_->parent;
    }
    // Go up one more time
    return *this;
} 


//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{ 
	Node* p = root;
	while(p->left){
		p = p->left;
	}
	return rope_iterator(p);
} 

Rope::Rope(){
	root = NULL;
	size_ = 0;
}

//This funtion will find the size of the rope
int Rope::find_size(Node* p){
	if(!p) return 0;
	int size = 0;
	if(!p->right){
		size = p->weight;
		return size;
	}
	while(p){
		size += p->weight;
		p = p->right;	
	}
	return size;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	if(!p->right){
		size_ = p->weight;
		p = NULL;
		delete p;
		return;
	}
	size_ = 0;
	while(p){
		size_ += p->weight;
		p = p->right;	
 }
	p = NULL;
	delete p;
}

//Destructor
Rope::~Rope(){
	this->destroy_rope(root);
}

//Constructor
Rope::Rope(const Rope& r){
	size_ = r.size_;
	root = this->copy_rope(r.root);
}

//Assignment operator
Rope& Rope::operator= (const Rope& r){
	if (&r != this) {
      this->destroy_rope(root);
      root = this->copy_rope(r.root);
      size_ = r.size_;
    }
    return *this;
}

//Destroy funtion
void Rope::destroy_rope(Node* p){	
	if(!p){
		delete p;
		return;
	}
	if(p->left) destroy_rope(p->left);
	if(p->right) destroy_rope(p->right);
	p = NULL;
	delete p;
}

//test function
void Rope::change_size(int i){
	size_ -= i;
}

//Copy funtion
Node* Rope::copy_rope(Node* old_root){
	if (!old_root) {return NULL;}
    Node* new_root = new Node(old_root->weight, old_root->value);
    if (old_root->left != NULL) {
      new_root->left = copy_rope(old_root->left);
    }
    if (old_root->right != NULL) {
      new_root->right = copy_rope(old_root->right);
    }
    return new_root;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	if(i > size_ || i < 0) return false;
	Node* p = this->root;
	while(p->left || p->right){
		if(i < p->weight){
			p = p->left;
		}
		else if(i >= p->weight){
			i -= p->weight;
			p = p->right;
		}
	}
	c = p->value[i];
	return true;
}

//This function will find the total weight of the leaf on the left side
//of the root/subroot
int Rope::find_length(Node* p){
	if(!p) return 0;
	if(!p->left && !p->right){
		return p->weight;
	}
	return find_length(p->left) + find_length(p->right);
}

//This function will find the weight of the root
int Rope::find_weight(Node *p){
	if(!p) return 0;
	if(p->left) return find_length(p->left);
	else return 0;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//Create a new root	
	Node* newroot = new Node();
	newroot->left = this->root;
	newroot->right = r.root;
	this->root->parent = newroot;
	r.root->parent = newroot;
	int new_size = this->size_ + r.size_;
	newroot->weight = find_length(newroot->left);
	this->root = newroot;
	this->size_ = new_size;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	if(j<i || i<0 || j<0 || i>size_ || j>size_) return false;
	s = "";
	char c;
	for(int k = i; k<=j; k++){
		index(k,c);
		s.push_back(c);
	}
	assert(s.size() == j-i+1);
	return true;
}

//This function will find the leaf node that we need to cut 
//And will return the path of the node that we need to cut to
//get the string after index.
void Rope::find_node_in_index(int &index, Node* p, vector<Node*> &path){
	//If !p or index > size or index < 0 => not exist => return 
	if(!p || index > this->size_ || index < 0) return;
	if(!p->left && !p->right){
		path.push_back(p);
		return;
	} 
	//If index => weight go right
	if(index >= p->weight){
		index -= p->weight;
		find_node_in_index(index, p->right, path);
	}
	//If index < weight go left
	else{
		path.push_back(p);
		find_node_in_index(index, p->left, path);
	}
}

//This function will recalculate the weight of the whole rope
void Rope::reconstruct(Node* &p){
	if(!p) return;
	if(!p->left && !p->right){
		p->weight = p->value.size();
		return;
	}
	else{
		p->weight = this->find_weight(p);
	} 
	reconstruct(p->left);
	reconstruct(p->right);
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	if(i < 0 || i > this->size_) return *this;
	vector<Node*> path;
	this->find_node_in_index(i, this->root, path);
	//If i == 0 => we just the leaf node and the node after it
	if(i == 0){
		//If the node is the left child
		if(path[path.size()-1] == path[path.size()-1]->parent->left){
			path[path.size()-1]->parent->left = NULL;
			path[path.size()-1]->parent = NULL;
		}
		//If the node is the right child
		else{
			path[path.size()-1]->parent->right = NULL;
			path[path.size()-1]->parent = NULL;	
		}
		rhs = Rope(path[path.size()-1]);
		path.pop_back();
		//Cut the node after it and concat them into a new rope
		for(int j = path.size()-1; j>=0; j--){
			if(path[j]->right){
				path[j]->right->parent = NULL;
				Rope right(path[j]->right);
				path[j]->right = NULL;
				rhs.concat(right);
			}
		}
		//Recalculate the whole rope
		reconstruct(this->root);
		reconstruct(rhs.root);
		this->size_ = find_size(this->root);
		return *this;
	}
	//If index != 0 => we will have to create 2 news leaf whose parent
	//is the original leaf, and then we start the split
	else{
		//Create 2 new leaf nodes
		Node* temp_node = path[path.size()-1];
		path.pop_back();
		string left_str = temp_node->value.substr(0,i);
		string right_str = temp_node->value.substr(i);
		Node* left_node = new Node();
		left_node->value = left_str;
		left_node->parent = temp_node;
		left_node->weight = left_str.size();
		Node* right_node = new Node();
		right_node->value = right_str;
		right_node->weight = right_str.size();
		temp_node->left = left_node;
		temp_node->value = "";
		
		//Start the cut
		path.push_back(right_node);
		rhs = Rope(path[path.size()-1]);
		path.pop_back();
		for(int j = path.size()-1; j>=0; j--){
			if(path[j]->right){
				path[j]->right->parent = NULL;
				Rope right(path[j]->right);
				path[j]->right = NULL;
				rhs.concat(right);
			}
		}
		//Recalculate the whole rope
		reconstruct(this->root);
		reconstruct(rhs.root);
		this->size_ = find_size(this->root);
		return *this;
	}
	//If we cut from the start of the string value
	//for(int j = 0; j<path.size(); j++) cout<<path[j]->weight<<endl;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//assert(0 && "Rope split() not implemented!");
}

