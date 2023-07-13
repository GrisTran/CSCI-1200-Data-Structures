// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
using namespace std;

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  map<string, pair<int, map<string, int > > > MY_MAP;
typedef map<string, pair<int, MY_MAP> >  MY_MAP3;
typedef map<string, int>::iterator mtr;
//STRUCTURE FOR WINDOW > 3
typedef map<vector<string>, vector<int> > VMAP;
typedef map<vector<string>, map<string, int> > AMAP;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
	char c;
 	word.clear();
	while (istr) {
    // just "peek" at the next character in the stream
    	c = istr.peek();
    	if (isspace(c)) {
      	// skip whitespace before a word starts
      		istr.get(c);
     		if (word != "") {
			// break words at whitespace
				return true;
      		}
    	} 
		else if (c == '"') {
      	// double quotes are a delimiter and a special "word"
      		if (word == "") {
				istr.get(c);
				word.push_back(c);
      		}
      		return true;
    	} 
		else if (isalpha(c)) {
     	// this a an alphabetic word character
      		istr.get(c);
      		word.push_back(tolower(c));
    	} 
		else {
      	// ignore this character (probably punctuation)
      		istr.get(c);
    	}
  	}
  	return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleTextWin2(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  string word;
  string pre_word;
  MY_MAP::iterator itr;
  mtr itr2;
  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
    itr = data.find(word);
    if(itr == data.end()){
    	map<string, int> sample_map;
    	data.insert(make_pair(word, make_pair(1, sample_map) ) );
	}
	else{
		itr->second.first++;
	}
	if(pre_word != ""){
		itr2 = data[pre_word].second.find(word);
		if(itr2 != data[pre_word].second.end()){
			data[pre_word].second[word]++;
		}
		else{
			data[pre_word].second.insert(make_pair(word, 1));
		}
	}
	pre_word = word;
  }
}

// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (= 3) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleTextWin3(MY_MAP3 &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  string word;
  string sec_word = "";
  string first_word = "";
  MY_MAP3::iterator itr;
  MY_MAP::iterator itr2;
  map<string, int>::iterator itr3;
  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
    itr = data.find(word);
    if(itr == data.end()){
    	MY_MAP sample_map;
    	data.insert(make_pair(word, make_pair(1, sample_map) ) );
	}
	else{
		itr->second.first++;
	}
	if(first_word != ""){
		itr2 = data[first_word].second.find(sec_word);
		if(itr2 != data[first_word].second.end()){
			data[first_word].second[sec_word].first++;
		}
		else{
			map<string, int> sample_map2;
			data[first_word].second.insert(make_pair(sec_word,make_pair(1, sample_map2)));
		}
		itr3 = data[first_word].second[sec_word].second.find(word);
		if(itr3 != data[first_word].second[sec_word].second.end()){
			data[first_word].second[sec_word].second[word]++;
		}
		else{
			data[first_word].second[sec_word].second.insert(make_pair(word, 1));
		}
	}
    first_word = sec_word;
    sec_word = word;
  }
}

// HELP FUNCTIONS FOR THE CASE WHERE WINDOW > 3---------------------------------------------------------------------------------------


// LoadSampleText_LargeWindowCase funtion
// Loads the sample text from the file, storing it in a vector<string> and return it
vector<string> LoadSampleText_LargeWindowCase(const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  string word;
  vector<string> words;
  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
    words.push_back(word);
  }
  return words;
}

//getIndicates funtion
//This function will find a vector<string> of size window-1
//and set it as the key value for the VMAP type of value.
//The second value which is a vector<int> will store the index
//of the head_string in the keyvalue.
//	For Example:
//I have a vector<int> {1,2,1,3,4,5,1,2,1,3}
//With window size = 4, I will have a VMAP value and
//VMAP[{1,2,1}] will have second value as {0,6}
// You can see that {1,2,1} appear 2 times with the head index at 0 and 6.
VMAP getIndicates(vector<string> str, int size ){
	map<vector<string>, vector<int> > indicates;
	int n = str.size();
	for(int i  = 0; i<=n-size+1; i++){
		vector<string> indicate;
		for(int j = i; j< i+size-1; j++){
			indicate.push_back(str[j]);
		}
		if(indicates.find(indicate) == indicates.end()){
			vector<int> index;
			index.push_back(i);
			indicates.insert(make_pair(indicate, index));
		}
		else{
			indicates[indicate].push_back(i);
		}
	}
	return indicates;
}

//Solve function
//This function will return an AMAP type data which is a 
// map with a vector<string> as the key value which store 
//The number of string equal to window - 1 and it will have the
//map<string, int> as a second value which store the word after the
//key value and the number of its appearance.
AMAP solve_all_win( map<vector<string>, vector<int> > indicates, unsigned int size, vector<string> str){
	map<vector<string>, map<string, int> > answer;
	map<vector<string>, vector<int> >::iterator itr;
	for(itr = indicates.begin(); itr != indicates.end(); itr++){
		map<string, int> inmap;
		for(unsigned int i = 0 ; i<itr->second.size() ; i++){
			//If index + window -1 out of bounce of vector<string> str
			if(int(itr->second[i]) + size-1 >= str.size()) continue;
			if(inmap.find( str[itr->second[i] + (size-1)] ) == inmap.end()){
				inmap.insert(make_pair(str[itr->second[i] + (size-1)], 1));
			}
			else{
				inmap[str[itr->second[i] + (size-1)]]++;
			}
		}
		answer.insert(make_pair(itr->first, inmap));
	}
	return answer;
}



//MAIN FUNCTION--------------------------------------------------------------------------------------------------------
int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;
  MY_MAP3 data2;
  unsigned int window;      //window need to be out here because it is needed for print command.
  // VARIABLE FOR WINDOW > 3
  vector<string> all_words;
  vector<pair<AMAP, VMAP> > answer_vec;

  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;  
	  //ASSGINMENT START    
      cout <<"Loaded "<< filename<<" with window = "<< window <<" and parse method = "<<parse_method<<endl<<endl;
      //If window size = 2
      if(window == 2){
      	LoadSampleTextWin2(data, filename, window, parse_method);
	  } 
	  //If window size = 3
      else if(window == 3){
      	LoadSampleTextWin3(data2, filename, window, parse_method);
	  }
	  else if(window > 3){
	  	unsigned int count = window;
	  	all_words = LoadSampleText_LargeWindowCase(filename, window, parse_method);
	  	while(count > 1){
	  		VMAP help_data;
	  		AMAP main_data;
	  		help_data = getIndicates(all_words, count);
	  		main_data = solve_all_win(help_data, count, all_words);
	  		answer_vec.push_back(make_pair(main_data, help_data));	
	  		count--;
		}
	  }
    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      //If window = 2 => We only need to handle the case that sentence.size() = 1.
      if(window == 2){
      	//Check if the word is in the data or not
      	MY_MAP::iterator it = data.find(sentence[0]);
      	if(it == data.end()){
      		cout<<sentence[0] << " (0)" << endl;	
		}
		//If word is in the data, we print the data out
		else{
			cout<<sentence[0]<<" ("<<it->second.first<<")"<<endl;
			for(mtr itr = it->second.second.begin(); itr != it->second.second.end(); itr++){
          		cout<<sentence[0]<<" "<<itr->first<<" ("<<itr->second<<")"<<endl;
        	}
        	cout <<endl;
		}
	  }
	  //If window = 3 => We will have to handle 2 case sentence.size() = 1 and sentence.size() = 2.
	  if(window == 3){
	  	//Prepare iterator variable
	  	MY_MAP3::iterator itr;
	  	MY_MAP::iterator itr2;
	  	mtr itr3;
	  	//If sentence.size() = 1
	  	if(sentence.size() == 1){
	  		//Check to see if the word is in the data2 or not
	  		itr = data2.find(sentence[0]);
	  		if(itr == data2.end()){
	  			cout<<sentence[0]<<" (0)"<<endl;
			}
			//If the word is in the data2, we print it out
			else{
				cout<<sentence[0]<<" ("<<itr->second.first<<")"<<endl;
				for(itr2 = itr->second.second.begin(); itr2 != itr->second.second.end(); itr2++){
					cout<<sentence[0]<<" "<<itr2->first<<" ("<<itr2->second.first<<")"<<endl;
				}
				cout<<endl;
			}
		}
		//If sentence.size() = 2
		else if(sentence.size() == 2){
			itr = data2.find(sentence[0]);
			itr2 = data2[sentence[0]].second.find(sentence[1]);
			//Check to see if the words are in data2 or not
			if(itr == data2.end() || itr2 == data2[sentence[1]].second.end()){
				cout<<sentence[0]<<" "<<sentence[1]<<" (0)"<<endl;
			}
			//If words are in data2, we print their data out
			else{
				cout<<sentence[0]<<" "<<sentence[1]<<" ("<<itr->second.second[sentence[1]].first<<")"<<endl;
				for(itr3 = itr->second.second[sentence[1]].second.begin(); itr3 != itr->second.second[sentence[1]].second.end(); itr3++){
					cout<<sentence[0]<<" "<<sentence[1]<<" "<<itr3->first<<" ("<<itr3->second<<")"<<endl;
				}
				cout<<endl;
			}
		}	
	   }
	   //For window > 3 and sentence of all size < window
	  else if(window > 3 && sentence.size() < window){
	  	//typedef map<vector<string>, vector<int> > VMAP;
		//typedef map<vector<string>, map<string, int> > AMAP;
	   	unsigned int win_index = window - sentence.size() - 1;
	   	//This vector will be use to find the right place in the map ad a key value in []
	   	vector<string> find_vec = sentence;
	   	AMAP::iterator atr;
	   	for(unsigned int i = 0; i<answer_vec.size(); i++){
	   		if(i == win_index){
	   			atr = answer_vec[i].first.find(find_vec);
	   			if(atr == answer_vec[i].first.end()){
	   				for(unsigned int j = 0; j < find_vec.size(); j++){
	   					cout<<find_vec[j]<<" ";	
					}
					cout<<"(0)"<<endl;	
				}
				else{
					for(unsigned int j = 0; j < find_vec.size(); j++){
	   					cout<<find_vec[j]<<" ";	
					}
					cout<<"("<<answer_vec[i].second[find_vec].size()<<")"<<endl;
					for(mtr id = atr->second.begin(); id != atr->second.end(); id++){
						for(unsigned int k = 0; k < find_vec.size(); k++){
	   						cout<<find_vec[k]<<" ";	
						}
						cout<<id->first<<" ("<<id->second<<")"<<endl;
					}
					cout<<endl;
				}
			}
		}
	   }
	}	
    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
		random_flag = true;
      } 
	  else {
		assert (selection_method == "most_common");
		random_flag = false;
      }
      // If not random_flag => Common case
      if(!random_flag){
      	//If window = 2
      	//The idea for most_common case is that we will go through all the word 
      	//in the map of the word given and find the most common one to print out.
      	//There will be 3 cases that we need to look at:
      	//	Case 1:
      	//If word a have more apearances than word be, we choose a as the max word
      	//	Case 2:
      	//If word a have equal apearances to most_common and the max_word vector is
      	//empty => word a is the first word in the map => we choose word a to push back
      	//inside the max_word vector and go to the next loop.
      	//	Case 3:
      	//If word a have equal apearances to most_common and the max_word vector is not
      	//empty => we compare the 2 word (word a and max_Word[0]) and choose the next word
      	//aphabetically.
      	if(window == 2 && sentence.size() == 1){
      		//For window 2, we just need to handle 1 case which is sentence.size() = 1
      		cout<<sentence[0];
      		string curr_str = sentence[0];
      		int most_common = 1;
      		vector<string> max_word;
      		MY_MAP::iterator it = data.find(sentence[0]);
      		while(length--){
      			for(mtr ptr = it->second.second.begin(); ptr != it->second.second.end(); ptr++){
      				if(ptr->second > most_common){
      					most_common = ptr->second;
      					max_word.clear();
						max_word.push_back(ptr->first);	
					}
					else if(ptr->second == most_common && max_word.size() == 0){
						max_word.push_back(ptr->first);
					}
					else if(ptr->second == most_common && max_word.size() == 1){
						if(max_word[0] > ptr->first){
							max_word.clear();
							max_word.push_back(ptr->first);
						}
					}
				}
				cout<<" "<<max_word[0];
				it = data.find(max_word[0]);
				most_common = 1;
				//Clear the max_word vector before going to the next loop to avoid duplicate
				max_word.clear();
			}
			cout<<endl<<endl;
		}
		//If window = 3
		if(window == 3){
			//If window size = 3, we will need to handle the case sentence.size() = 1 and = 2
			//The idea to find the most common word stay the same for all window size
			vector<string> sample = sentence;
			//If sentence size = 1, we find the most common word after the sentence[0] and then find the 
			//phrase base on sentence[0] and the most common word after it.
  			if(sentence.size() == 1){
  				cout<<sentence[0];
				string curr_str = sentence[0];
				int most_common = 1;
				vector<string> max_word;	
				MY_MAP3::iterator it = data2.find(sentence[0]);
				MY_MAP::iterator it2;
				for(it2 = it->second.second.begin(); it2 != it->second.second.end(); it2++){
					if(it2->second.first > most_common){
						most_common = it2->second.first;
						max_word.clear();
						max_word.push_back(it2->first);
					}
					else if(it->second.first == most_common && max_word.size() == 0){
						max_word.push_back(it2->first);
					}
					else if(it->second.first == most_common && max_word.size() == 1){
						if(max_word[0] > it2->first){
							max_word.clear();
							max_word.push_back(it2->first);
						}
					}
				}
				cout<<" "<<max_word[0];
				sample.push_back(max_word[0]);
				//We will have to decrease the length by 1 because we just find 1 common_word
				length--;
			}
			//If sentence size = 1, we will just have to find the phrase base
			//on sentence[0] and sentence[1]
			else{
				cout<<sample[0]<<" "<<sample[1];
			}
			int most_common = 1;
			vector<string> max_word;
			string index = sample[1];
			MY_MAP3::iterator it = data2.find(sample[0]);
			MY_MAP::iterator it2;
			mtr it3;
			while(length--){
				for(it3 = it->second.second[index].second.begin(); it3 != it->second.second[index].second.end(); it3++){
					if(it3->second > most_common){
						most_common = it3->second;
						max_word.clear();
						max_word.push_back(it3->first);
					}
					else if(it3->second == most_common && max_word.size() == 0){
						max_word.push_back(it3->first);
					}
					else if(it3->second == most_common && max_word.size() == 1){
						if(max_word[0] > it3->first){
							max_word.clear();
							max_word.push_back(it3->first);
						}
					}
				}
				cout<<" "<<max_word[0];
				//Index will be the head word for next loop
				it = data2.find(index);
				//Reset the string index
				index = max_word[0];
				//Clear the max_word vector before going to the next loop to avoid duplicate
				max_word.clear();
				//Reset most_common back to 1
				most_common = 1;
			}
			cout<<endl<<endl;		
		}
	  }
	  //Random case
	  else{
	  	// The idea of to solve the random case is that we will put every loop
	  	//into a vector string. After that, we have an int called index and it value will
	  	//equal to rand() %vector<string>.size().
	  	//After that, we will have vec[index] as our next random word.
	  	//Check to make sure it is the random case
	  	assert(random_flag);
	  	//If window = 2
	  	if(window == 2){
	  		cout<<sentence[0];	
	  		string curr_str = sentence[0];
	  		MY_MAP::iterator it = data.find(sentence[0]);
	  		vector<string> random_vec;
	  		while(length--){
      			for(mtr ptr = it->second.second.begin(); ptr != it->second.second.end(); ptr++){
      				random_vec.push_back(ptr->first);
				}
				int index = rand() % random_vec.size();
				curr_str = random_vec[index];
				cout<<" "<<curr_str;
				it = data.find(curr_str);
				//Clear the random_vec before going to the next loop to avoid duplicate
				random_vec.clear();
			}
			cout<<endl<<endl;
		}
		//If window = 3
		if(window == 3){
			//If window = 3, we use the same idea with the most common case on how
			// we handle the 2 case sentence.size() = 1 and = 2
			vector<string> sample = sentence;
			if(sentence.size() == 1){
				//If sentence.size() = 1, we will find 1 random word next to sentence[0]
				// and find the random phrase base on sentence[0] and the random word after it.
				cout<<sentence[0];
				vector<string> random_vec;	
				MY_MAP3::iterator it = data2.find(sentence[0]);
				MY_MAP::iterator it2;
				for(it2 = it->second.second.begin(); it2 != it->second.second.end(); it2++){
					random_vec.push_back(it2->first);
				}
				int index = rand() % random_vec.size();
				cout<<" "<<random_vec[index];
				sample.push_back(random_vec[index]);
				length--;
			}
			else if(sentence.size() == 2){
				//If sentence.size() = 2, we will find the random phrase base on 
				//sentence[0] and sentence[1].
  				cout<<sample[0]<<" "<<sample[1];
			}
			string index = sample[1];
			//Prepare the iterator variable
			MY_MAP3::iterator it = data2.find(sample[0]);
			mtr it3;
			while(length--){
				vector<string> random_vec;
				for(it3 = it->second.second[index].second.begin(); it3 != it->second.second[index].second.end(); it3++){
					random_vec.push_back(it3->first);
				}
				//Generate a random index
				int position = rand() % random_vec.size();
				cout<<" "<<random_vec[position];
				//The current index will be the head word for the next loop
				it = data2.find(index);
				//Reset the index string
				index = random_vec[position];
				//Although we redefine random_vec at the start of every loop
				//I will just clear it to avoid bug.
				random_vec.clear();
			}
			cout<<endl<<endl;	
		}
	  }


      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //


    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
