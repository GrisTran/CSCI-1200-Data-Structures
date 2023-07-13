//Homework 9
//Gris Tran
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
using namespace std;

//CLASSES
#include "movie.h"

//MAP STRUCTURE
typedef vector<pair<QUERY, list<MOVIE_DATA> > > HASH_TABLE;
typedef map<string, string> Actor_map;
typedef HASH_TABLE::iterator htr;
typedef Actor_map::iterator atr;

//HELPER FUNCTIONS TO READ DATA==========================================================
//Read Actor File
//This function will read the actor infile and process it into a map<string, string>
//data type with the actor code is key and the value is the actor name
void ReadActorFile(const string &filename, Actor_map &actor){
	actor.clear();
	vector<string> actor_vec;
	string line;
	ifstream infile;
	infile.open(filename.c_str());
	//If cannot open file
	if (!infile) { 
    	std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    	exit(1);
  	} 
  	while(infile >> line){
  		actor_vec.push_back(line);
	}
	infile.close();
	for(unsigned int i = 0; i < actor_vec.size(); i+=2){
		actor[actor_vec[i]] = actor_vec[i+1];
	}
}

//Read Movie File
//This funtion will read the infile for movie data and return a vector<string>
//contain all of the information
void ReadMovieFile(const string &filename, vector<string> &movie_vec){
	string line;
	ifstream infile;
	infile.open(filename.c_str());
	if (!infile) { 
    	std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    	exit(1);
  	} 
  	while(infile >> line){
  		movie_vec.push_back(line);
	}
	infile.close();
}

//Process Movie File
//This funtion will process a vector string returned from the ReadMovieFile
//and return a vector<MOVIE_DATA> which contain all of the MOVIE_DATA type value
vector<MOVIE_DATA> ProcessMovieVec(vector<string> &vec){
	vector<MOVIE_DATA> mvec;
	//Call the constructor for the first 3 variables: title, time and year.
	//The reason I call constructor on these 3 variable independently from the others
	//is because it dont have a list goes along with it
	for(int i = 0; i<vec.size() - 3;){
		int plus_size;
		mvec.push_back(MOVIE_DATA(vec[i], vec[i+1], vec[i+2]));
		i += 2;
		//Increase the i value to move to the next start position
		plus_size = atoi(vec[i+1].c_str());
		i += plus_size + 1;
		plus_size = atoi(vec[i+1].c_str());
		i+= plus_size + 1;
		plus_size = atoi(vec[i+1].c_str());
		i+= plus_size + 2;
	}
	//Now we find the other variables of the MOVIE_DATA value
	//The idea is that we will use a track value to know which part we are in. If the
	//initial int for actor, genre, role is > 0, we add the vector<String> of those value into
	//our MOVIE_TYPE value, else, we add an empty vector<String>
	int track = 3;
	int movie_track = 0;
	for(int i = 0; i<vec.size(); i+=6){
		//Initial condition: track will always < vec.size
		if(track < vec.size() && movie_track < mvec.size()){
			vector<string> addvec;
			int genre_size = atoi(vec[track].c_str());
			addvec.clear();
			//Check for genre
			while(genre_size > 0){
				track++;
				addvec.push_back(vec[track]);
				genre_size--;
			}
			mvec[movie_track].addGenre(addvec);
			int actor_size = atoi(vec[track + 1].c_str());
			addvec.clear();
			//Check for actor
			while(actor_size > 0){
				track++;
				addvec.push_back(vec[track + 1]);
				actor_size--;
			}
			mvec[movie_track].addActor(addvec);
			int role_size = atoi(vec[track + 2].c_str());
			addvec.clear();
			//CHeck for role
			while(role_size > 0){
				track++;
				addvec.push_back(vec[track + 2]);
				role_size--;
			}
			mvec[movie_track].addRole(addvec);
			movie_track++;
			track += 6;
		}
	}
	return mvec;
}

//Read Query Data
//This funtion is use to read the QUERY data put in by call getline()
//the logic is same with the ProcessMovieVec funtion
QUERY ReadQueryData(){
	string value;
	string title;
	string time;
	string role;
	cin>>title>>time>>role;
	cin.ignore();
	QUERY query(title, time, role);
	string word;
	int cal = 0;
	while(cal < 3){
		vector<string> add_data;
		getline(cin, word);
		int c = atoi(word.substr(0,word.find(" ")).c_str());
		while(c > 0){
			if(c == 1){
				//There will be a space between every word in a line/list so I use substr to seperate them
				word = word.substr(word.find(" ")+1);
				add_data.push_back(word.substr(0, word.find(" ")));
				c--;
			}
			else{
				word = word.substr(word.find(" ")+1);
				add_data.push_back(word.substr(0, word.find(" ")));
				c--;	
			}
		}
		//0 mean genre, 1 mean actor, 2 mean role
		if(cal == 0) query.addGenre(add_data);
		else if(cal == 1) query.addActor(add_data);
		else if(cal == 2) query.addRole(add_data);
		cal++;
	}
	return query;
}

//HASH RELATED FUNCTION============================================================================
//Hash funtion
//This hash funtion is the idea of Quadratic probing from lecture 20
int MovieHash(const QUERY &key_data, const HASH_TABLE &data){
	int year_hash;
	//If year == wildcard i will consider it as 2020
	if(key_data.getYear() == "?") year_hash = 2022;
	else year_hash = atoi(key_data.getYear().c_str());
	return year_hash % data.size();
}

//getMovieListByQuery
//This funtion is to get the movie list which is match the given query,
// I use a funtion call isMatch in the Query class for this function.
list<MOVIE_DATA> getMovieListByQuery(const QUERY key_data, const vector<MOVIE_DATA> &movie_vec){
	list<MOVIE_DATA> movie_list;
	QUERY compare_data = key_data;
	for(int i = 0; i<movie_vec.size(); i++){
		if(compare_data.isMatch(movie_vec[i])) movie_list.push_back(movie_vec[i]);
	}
	return movie_list;
}

//This funtion will double the size of the hash table
//The idea is I will store all of the value to a tmp vector.
//Then I will double the size by resize and then insert everything
//back in with my hash idea.
void resize(HASH_TABLE &data){
	int newsize = data.size()*2;
	HASH_TABLE memory = data;
	data.clear();
	list<MOVIE_DATA> sample_list;
	data.resize(newsize, make_pair(QUERY(), sample_list));
	for(int i = 0; i<memory.size(); i++){
		if(!memory[i].first.isDefault()){
			int index = MovieHash(memory[i].first, data);
			int h = 1;
			while(!data[index].first.isDefault()){
				index = (index + h*h) % data.size();
				h++;
			}
			data.push_back(memory[i]);
		}
	}
}

//Handle Occupancy 
//This funtion will calculate the occupancy every time we insert, if
//the curr occupancy > limit => resize the hash table
void HandleOccupancy(HASH_TABLE &data, const float occupancy){
	int filled = 0;
	for(int i = 0; i<data.size(); i++){
		if(!data[i].first.isDefault()) filled++; 
	}
	float curr_occupancy = (float)filled/data.size();
	if(curr_occupancy > occupancy) resize(data);
}

//Insert Movie
//This funtion will insert pair<query, list<movie_data>> into the HASH_TABLE container
//This hash funtion is the idea of Quadratic probing from lecture 20
void MovieHashInsert(const QUERY &key_data, HASH_TABLE &data, list<MOVIE_DATA> movie_list, const float occupancy){
	int index = MovieHash(key_data, data);
	int h = 1;
	while(!data[index].first.isDefault()){
		index = (index + h*h) % data.size();
		h++;
	}
	data[index] = make_pair(key_data, movie_list);
}

//MAIN FUNCTION================================================================================
int main(){
	// ASSIGNMENT: THE MAIN DATA STRUCTURE
	list<MOVIE_DATA> sample_list;
	HASH_TABLE data(100, make_pair(QUERY(), sample_list));
	Actor_map actor;
	vector<MOVIE_DATA> movie_vec;
	float occupancy = 0.5;
	
	// Parse each command
 	std::string command;    
 	while (cin >> command) {		
 		if(command == "table_size"){
 			int n;
 			cin>>n;
 			data.resize(n);
		}
		else if(command == "occupancy"){
			cin>>occupancy;
		}
		else if(command == "movies"){
			string filename;
			cin>>filename;
			vector<string> movie_vector;
			ReadMovieFile(filename, movie_vector);
			movie_vec = ProcessMovieVec(movie_vector);
			//for(int i = 0; i<movie_vec.size(); i++) movie_vec[i].print_movie();
		}
		else if(command == "actors"){
			string filename;
			cin>>filename;
			ReadActorFile(filename, actor);
			map<string, string>::iterator it;
			/*
			for(it = actor.begin(); it != actor.end(); it++){
				cout<<it->first<<" and "<<it->second<<endl;
			}
			*/
		}
		else if(command == "query"){
			QUERY query_key = ReadQueryData();
			list<MOVIE_DATA> match_list = getMovieListByQuery(query_key, movie_vec);
			MovieHashInsert(query_key, data, match_list, occupancy);
			if(match_list.empty()){
				cout<<"No results for query."<<endl;
			}
			else{
				cout<<"Printing "<<match_list.size()<<" result(s):"<<endl;
				for(list<MOVIE_DATA>::iterator it = match_list.begin(); it != match_list.end(); it++){
					(*it).print_movie(actor);
				}
			}
		}
 		else if(command == "quit"){
 			break;
		}
		else{
			cout << "WARNING: Unknown command: " << command << endl;
		}
 	} 
}
