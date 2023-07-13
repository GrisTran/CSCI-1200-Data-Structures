#ifndef movie_h_
#define movie_h_
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class MOVIE_DATA{
public:
	//CONSTRUCTOR
	MOVIE_DATA(){
		
	}
	MOVIE_DATA(string title_, string year_, string time_){
		this->title = title_;
		this->year = year_;
		this->time = time_;
	}
	
	//ACCESOR
	//These funtion will return the protected variable
	string getTitle() const{
		return this->title;
	}
	string getYear() const{
		return this->year;
	}
	string getTime() const{
		return this->time;
	}
	int getGenres() const{
		return this->genres;
	}
	vector<string> getGenresList() const{
		return this->genres_list;
	}
	int getActor_code() const{
		return this->actor_code;
	}
	vector<string> getActorList() const{
		return this->actor_list;
	}
	int getRole() const{
		return this->role;
	}
	vector<string> getRoleList() const{
		return this->role_list;
	}
	
	
	//MODIFIER
	void addActor(vector<string> avec){
		this->actor_code = avec.size();
		actor_list = avec;
	}
	void addGenre(vector<string> gvec){
		this->genres = gvec.size();
		genres_list = gvec;
	}
	void addRole(vector<string> rvec){
		this->role = rvec.size();
		role_list = rvec;
	}
		
	//HELPER FUNTION
	void print_movie(map<string, string> actor){
		cout<<title<<endl;
		cout<<year<<endl;
		cout<<time<<endl;
		cout<<genres;
		for(int i = 0; i < genres_list.size(); i++) cout<<" "<<genres_list[i];
		cout<<endl;
		cout<<actor_code;
		for(int i = 0; i < actor_list.size(); i++){
			cout<<" "<<actor[actor_list[i]];
			cout<<" ("<<role_list[i]<<")";	
		} 
		cout<<endl;
	}
protected:
	string title;
	string year;
	string time;
	int genres;
	vector<string> genres_list;
	int actor_code;
	vector<string> actor_list;
	int role;
	vector<string> role_list;
};

class QUERY : public MOVIE_DATA {
public:
	//CONSTRUCTOR
	QUERY(){
		MOVIE_DATA();
		this->default_ = true;
	}
	QUERY(string title_, string year_, string time_) : MOVIE_DATA(title_, year_, time_) {this->default_ = false;}
	
	//HELPER FUNCTION
	bool isDefault(){
		return this->default_;
	}
	bool isMatch(const MOVIE_DATA &data){
		//If not wild card and not equal => false
		if(this->title != "?" && this->title != data.getTitle()) return false;
		if(this->year != "?" && this->year != data.getYear()) return false;
		if(this->time != "?" && this->time != data.getTime()) return false;
		if(this->genres != 0){
			if(this->genres != data.getGenres()) return false;
			vector<string> genre_vec1 = data.getGenresList();
			vector<string> genre_vec2 = this->genres_list;
			for(int i = 0; i<this->genres; i++){
				if(genre_vec1[i] != genre_vec2[i]) return false;
			}
		}
		//If not wild card we have to check the order of the list
		//Elese if it is wild card then dont have to check
		if(this->actor_code != 0){
			if(this->actor_code != data.getActor_code()) return false;
			vector<string> actor_vec1 = data.getActorList();
			vector<string> actor_vec2 = this->actor_list;
			for(int i = 0; i<this->actor_code; i++){
				if(actor_vec1[i] != actor_vec2[i]) return false;
			}
		}
		if(this->role != 0){
			if(this->role != data.getRole()) return false;
			vector<string> role_vec1 = data.getRoleList();
			vector<string> role_vec2 = this->role_list;
			for(int i = 0; i<this->role; i++){
				if(role_vec1[i] != role_vec2[i]) return false;
			}
		}
		return true;

	}
	//Operator =
	QUERY& operator=(const QUERY &q){
		this->title = q.title;
		this->time = q.time;
		this->year = q.year;
		this->genres = q.genres;
		if(this->genres != 0){
			this->genres_list = q.genres_list;
		}
		this->actor_code = q.actor_code;
		if(this->actor_code != 0){
			this->actor_list = q.actor_list;
		}
		this->role = q.role;
		if(this->role != 0){
			this->role_list = q.role_list;
		}
		return *this;
	} 
	
	
	
private:
	bool default_;	
};

#endif











