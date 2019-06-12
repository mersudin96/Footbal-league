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
unordered_map <string, League> leagues;

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
		cout<<welcome_msg<<endl;
		cin>>choice;
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

	}while(choice);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void addTeam(){
	cout<<"Enter name, country, city and stadion name: "<<endl;
	string a,b,c,d;
	cin>>a>>b>>c>>d;
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
	cout<<"Enter name, lastname of judge and country he is comeing from: "<<endl;
	cin>>temp.name>>temp.lastName>>temp.country;

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
	cout<<"Enter name and country of league: ";
	string n,c;
	cin>>n>>c;
	League l(n,c);

	if(leagues.size()){
		unordered_map<string,League>::const_iterator it = leagues.find(c);
		if(it!=leagues.end()){
			cout<<"League already exist!"<<endl<<endl;
			return;
		}
	}
	leagues[l.country] = l;
	cout<<"League successfully added!"<<endl<<endl;
}

void playMatch(){
	cout<<"Enter country: ";
	string c;
	cin>>c;
	unordered_map<string,League>::const_iterator iter = leagues.find(c);
	if(iter == leagues.end()){
		cout<<"League dont exist"<<endl<<endl;
		return;
	}else{
		leagues[c].printNextScheduledMatch();

		int a,b;
		cout<<"Team1 score: ";
		cin>>a;
		cout<<"Team2 score: ";
		cin>>b;

		string rez = to_string(a) +":" +to_string(b);
		auto it = leagues[c].notPlayedMatches.begin();

		int index1 = -1, index2 = -1;
		for(size_t i=0; i<leagues[c].tms.size(); ++i){
			if(leagues[c].tms[i] == it->team1)
				index1 = i;
			if(leagues[c].tms[i] == it->team2)
				index2 = i;
			if(index1 != -1 && index2 != -1)
				break;
		}
		if(a>b){
			leagues[c].tms[index1].points+=3;
			it->team1.points+=3;
		}
		else if(b>a){
			it->team2.points+=3;
			leagues[c].tms[index2].points+=3;
		}
		else{
			it->team1.points+=1;
			it->team2.points+=1;
			leagues[c].tms[index1].points+=1;
			leagues[c].tms[index2].points+=1;
		}

		leagues[c].notPlayedMatches.front().result = rez;
		leagues[c].playedMatches.push_back(leagues[c].notPlayedMatches.front());
		leagues[c].notPlayedMatches.erase(it);
		cout<<"Match finished!"<<endl<<endl;
	}

}

void printAllMatchesAllLeagues(){
	for(auto it = leagues.begin(); it!=leagues.end(); it++){
		cout<<"\t\t~"<<it->first<<" league~"<<endl<<"\t     ******************"<<endl;
		it->second.printPlayedMatches();
		it->second.printNotPlayedMatches();
		cout<<endl<<endl;
	}
}

void cancelLastMatch(){
	cout<<"Enter country where you want to cancel last match: ";
	string c;
	cin>>c;
	leagues[c].cancelLastMatch();
}

void printTeamInfo(){
	cout<<"Enter country of team and team name: ";
	string c,n;
	cin>>c>>n;
	leagues[c].printTeamPlayedMatches(n);
	leagues[c].printTeamNotPlayedMatches(n);
}

void dispResTable(){
	cout<<"Enter country of league: "<<endl;
	string s;;
	cin>>s;
	auto it = leagues.find(s);
	if(it != leagues.end())
		leagues[s].printPointsTable();
	else
		cout<<"No such country in league!"<<endl<<endl;
}
