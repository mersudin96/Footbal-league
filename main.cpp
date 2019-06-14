#include "team.h"
#include "judges.h"
#include "match.h"
#include "league.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <exception>
using namespace std;

vector <Team> teams;
vector <Judge> judges;
unordered_multimap <string, League> leagues; // više liga u jednoj državi

void addTeam();
void addJudge();
void addLeague();
void playMatch();
void cancelLastMatch();
void printTeamInfo();
void printAllMatchesAllLeagues();
void dispResTable();

string welcome_msg = "1. Add new team \n2. Add new judge \n3. Add new league \n4. Play match \n5. Cancel last match"
					 "\n6. Information about team \n7. Display results table \n8. Display matches in all leagues\n\n0. Exit\n";

int main(int argc, char **argv) {
	srand(time(NULL));
	int choice;
	do{

		try{
			cout<<welcome_msg<<endl;
			cin>>choice;
			if(cin.fail())
				throw string("Please enter a number!\n");
			cin.ignore();

			switch(choice){
				case 0: break;
				case 1: addTeam(); break;
				case 2: addJudge(); break;
				case 3: addLeague(); break;
				case 4: playMatch(); break;
				case 5: cancelLastMatch(); break;
				case 6: printTeamInfo(); break;
				case 7: dispResTable(); break;
				case 8: printAllMatchesAllLeagues(); break;
				default: cout<<"Wrong input! Try again.\n\n"; break;
			}
		}catch(string& s){
			cout<<s<<endl;
			cin.clear();
			cin.ignore();
			choice = -1;
		}catch(...){
			cout<<"\tUps! Something went wrong...!"<<endl<<endl;
			cin.clear();
			cin.ignore();
			choice = -1;
		}

	}while(choice);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void addTeam(){
	string a,b,c,d;
	cout<<"Enter name: ";
	getline(cin,a);
	cout<<"Country: ";
	getline(cin,b);
	cout<<"city: ";
	getline(cin,c);
	cout<<"Stadion name: ";
	getline(cin,d);
	Team temp(a,b,c,d);
	string n;

	bool exist = false;
	for(size_t i=0; i<teams.size(); ++i){
		if(teams[i] == temp){
			exist = true;
			break;
		}
	}
	if(!exist){
		teams.push_back(temp);
		cout<<"Team successfully added!"<<endl<<endl;
	}else
		cout<<"Team already exist!"<<endl<<endl;
}

void addJudge(){
	Judge temp;
	cout<<"Enter judge name: ";
	getline(cin,temp.name);
	cout<<"Lastname: ";
	getline(cin,temp.lastName);
	cout<<"Country he is comeing from: ";
	getline(cin,temp.country);

	bool exist = false;
	for(unsigned int i=0; i<judges.size(); ++i){
		if(judges[i] == temp){
			exist = true;
			break;
		}
	}
	if(!exist){
		judges.push_back(temp);
		cout<<"Judge successfully added!"<<endl<<endl;
	}else
		cout<<"Judge already exist!"<<endl<<endl;
}

void addLeague(){
	try{
		string n,c;
		cout<<"Enter name: ";
		getline(cin,n);
		cout<<"Country of league: ";
		getline(cin,c);
		League l(n,c);

		if(leagues.size()){
			unordered_map<string,League>::const_iterator it = leagues.find(c);
			if(it!=leagues.end() && it->second.getName() == n){
				cout<<"League already exist!"<<endl<<endl;
				return;
			}
		}
		leagues.insert(make_pair(c,l));
		cout<<"League successfully added!"<<endl<<endl;
	}catch(string& s){
		cout<<s<<endl<<endl;
		return;
	}
}

void playMatch(){
	string c,n;
	cout<<"Enter country: ";
	getline(cin,c);

	unordered_multimap<string,League>::iterator iter = leagues.find(c);
	if(iter == leagues.end()){
		cout<<"League dont exist"<<endl<<endl;
		return;
	}else{
		try{
			cout<<"League: ";
			getline(cin,n);
			bool exist = false;
			auto range = leagues.equal_range(c);
			string x;
			for(auto it = range.first; it!=range.second; ++it){
				x = it->second.getName();
				if(x == n){
					iter = it;
					exist = true;
					break;
				}
			}
			if(!exist){
				cout<<"League doesn't exist!"<<endl<<endl;
				return;
			}
			iter->second.printNextScheduledMatch();

			int a,b;
			cout<<"Team1 score: ";
			cin>>a;
			if(cin.fail())
				throw string("Wrong input!");
			cout<<"Team2 score: ";
			cin>>b;
			if(cin.fail())
				throw string("Wrong input!");

			pair<int,int> rez(a,b);
			auto it = iter->second.getNotPlayedMatches().begin();

			int index1 = -1, index2 = -1;
			for(size_t i=0; i<iter->second.getTms().size(); ++i){

				if(iter->second.getTms()[i] == it->team1)
					index1 = i;
				if(iter->second.getTms()[i] == it->team2)
					index2 = i;
				if(index1 != -1 && index2 != -1)
					break;
			}
			if(a>b){
				iter->second.getTms()[index1].addPoints(3);
				int a = 3;
				it->team1.addPoints(a);
			}
			else if(b>a){
				it->team2.points+=3;
				iter->second.getTms()[index2].addPoints(3);
			}
			else{
				it->team1.points+=1;
				it->team2.points+=1;
				iter->second.getTms()[index1].addPoints(1);
				iter->second.getTms()[index2].addPoints(1);
			}

			iter->second.getNotPlayedMatches().front().result = rez;
			Match c = iter->second.getNotPlayedMatches().front();
			iter->second.getPlayedMatches().push_back(c);
			iter->second.getNotPlayedMatches().erase(it);
			cout<<"Match finished!"<<endl<<endl;

		}catch(string& s){
			cout<<s<<endl<<endl;
		}
	}

}

void printAllMatchesAllLeagues(){
	for(auto it = leagues.begin(); it!=leagues.end(); it++){
		cout<<"Country: "<<it->first<<endl<<endl;
		cout<<"\t\t~"<<it->second.getName()<<" league~"<<endl<<"\t     ******************"<<endl;
		it->second.printPlayedMatches();
		it->second.printNotPlayedMatches();
		cout<<endl<<endl;
	}
}

void cancelLastMatch(){
	cout<<"Enter country where you want to cancel last match: ";
	string c;
	getline(cin,c);
	auto it = leagues.find(c);
	if(it == leagues.end()){
		cout<<"No such country in league!"<<endl;
		return;
	}else{
		auto r = leagues.equal_range(c);
		cout<<"Enter league name: "<<endl;
		string n;
		getline(cin,n);
		bool exist = false;
		for(auto it2 = r.first; it2!=r.second; it2++){
			if(it2->second.getName() == n){
				it = it2;
				exist = true;
				break;
			}
		}
		if(exist)
			it->second.cancelLastMatch();
		else
			cout<<"That league doesn't exist!"<<endl<<endl;
	}
}

void printTeamInfo(){
	string c,n;
	cout<<"Enter country of team: ";
	getline(cin,c);
	cout<<"Team name: ";
	getline(cin,n);
	auto it = leagues.find(c);
	if(it == leagues.end()){
		cout<<"No such country in league!"<<endl;
		return;
	}else{
		auto r = leagues.equal_range(c);
		bool teamExist = false;
		for(auto it2 = r.first; it2!= r.second; ++it2){
			for(size_t i= 0; i<it2->second.getTms().size(); ++i){
				if(it2->second.getTms()[i].name == n){
					cout<<"\nName: "<<it2->second.getTms()[i].name<<endl;
					cout<<"\nCountry: "<<it->second.getTms()[i].country<<endl;
					cout<<"\nCity: "<<it->second.getTms()[i].city<<endl;
					cout<<"\nStadion: "<<it->second.getTms()[i].stadionName<<endl;
					cout<<"\nPoints: "<<it->second.getTms()[i].points<<endl<<endl;
					it2->second.printTeamPlayedMatches(n);
					it2->second.printTeamNotPlayedMatches(n);
					teamExist = true;
					break;
				}
			}
		}
		if(!teamExist)
			cout<<"Team is not in any league!"<<endl;
	}
}

void dispResTable(){
	cout<<"Enter country of league: "<<endl;
	string s;;
	getline(cin,s);
	auto it = leagues.find(s);
	if(it != leagues.end()){
		cout<<"Enter league name: "<<endl;
		string l;
		getline(cin,l);
		auto r = leagues.equal_range(s);
		for(auto i = r.first;  i!=r.second; ++i){
			if(i->second.getName() == l){
				i->second.printPointsTable();
			}
		}
	}
	else
		cout<<"No such country in league!"<<endl<<endl;
}

