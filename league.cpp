#include "league.h"
#include "date.h"
#include "match.h"
#include <iostream>
#include <algorithm>
using namespace std;

extern vector <Team> teams;
extern vector <Judge> judges;

string dashedLine = "-----------------------------------------------------------";
string line = "___________________________________________________________\n";
string longerDashedLine = "-----------------------------------------------------------------------";
string longerLine = "_______________________________________________________________________\n";


League::League() { tms = teams; }
League::League(string n, string c) : name(n), country(c){
	for(size_t i=0; i<teams.size(); ++i){
		if(teams[i].country == country)
			tms.push_back(teams[i]);
	}
	generateMatches();
}

void League::generateMatches(){
	srand(time(NULL));
	Date d(1,1,2019);
	Judge c,c2;
	int counter = rand() % 4 +1;
	for(size_t i=0; i<tms.size(); ++i){
		for(size_t j=0; j<tms.size(); ++j){
			if(i==j) continue;
			while(c.country != country)
				c = judges[rand() % judges.size()];
			while(c2.country != country || c2 == c)
				c2 = judges[rand() % judges.size()];

			if(counter == 4){
				d.day += rand() % 7 +1;
				if(d.day > 31){
					d.day = 1;
					d.month ++;
					if(d.month >12){
						d.month = 1;
						d.year++;
					}
				}
				counter=rand() % 4;
			}
			counter++;

			Match m(tms[i], tms[j], c, c2, d);
			notPlayedMatches.push_back(m);
			c.country = c2.country = "x";
		}
	}
}

void League::printNextScheduledMatch() const {
	Match m = notPlayedMatches.front();
	cout<<"\n\nTeam1 \t\tTeam2 \tJudge \tJudge2 \tDate\n"<<line<<endl;
	std::cout<<m.team1.name<<"\t\t"<<m.team2.name<<"\t"<<m.mainJudge.name<<"\t"<<m.helpJudge.name<<"\t"<<m.date.day<<"."<<m.date.month<<"."<<m.date.year<<endl;
	cout<<dashedLine<<endl<<dashedLine<<endl;
}

void League::printPlayedMatches(){
	cout<<"\n\nTeam1 \t\tTeam2 \tJudge \t\tDate \t\tResult\n"<<line<<endl;
	for(size_t i=0; i<playedMatches.size(); ++i){
		cout<<playedMatches[i].team1.name<<"\t\t"<<playedMatches[i].team2.name<<"\t"<<playedMatches[i].mainJudge.name<<"\t"
				<<playedMatches[i].date.to_string()<<"\t"<<playedMatches[i].result<<endl;
		cout<<dashedLine<<endl;
	}
	cout<<dashedLine<<endl;
}

void League::printNotPlayedMatches(){
	cout<<"\n\nTeam1 \tTeam2 \tJudge \tDate\n"<<line<<endl;
	for (auto it = notPlayedMatches.begin(); it!= notPlayedMatches.end(); ++it){
		cout<<it->team1.name<<"\t"<<it->team2.name<<"\t"<<it->mainJudge.name<<"\t"<<it->date.to_string()<<endl;
		cout<<dashedLine<<endl;
	}
	cout<<dashedLine<<endl;
}

void League::cancelLastMatch(){
	if(playedMatches.size()){
		Match a = playedMatches[playedMatches.size()-1];
		a.result= "";
		notPlayedMatches.push_front(a);
		playedMatches.pop_back();
		cout<<"Match "<<a.team1.name<<" vs "<<a.team2.name<<" has been canceled"<<endl<<endl;
	}else
		cout<<"No match yet played!"<<endl<<endl;
}

void League::printTeamPlayedMatches(const string& s){
	cout<<"\n\t\t**Played matches** \n\t       ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ \nTeam1 \tTeam2 \tJudgeM \t\tJudgeH \t\tDate \t\tResult"<<endl;
	cout<<longerLine<<endl;
	for (size_t i=0; i<playedMatches.size(); ++i){
		if(playedMatches[i].team1.name == s || playedMatches[i].team2.name == s){
			cout<<playedMatches[i].team1.name<<"\t"<<playedMatches[i].team2.name<<"\t"<<playedMatches[i].mainJudge.name<<"\t"
					<<playedMatches[i].helpJudge.name<<"\t"<<playedMatches[i].date.to_string()<<"\t "<<playedMatches[i].result<<endl;
			cout<<longerDashedLine<<endl;
		}
	}
	cout<<longerDashedLine<<endl<<endl;
}

void League::printTeamNotPlayedMatches(const string& s){
	cout<<"\n\t    **Not played mathces** \n\t   ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ \nTeam1 \tTeam2 \tJudgeM \t\tJudgeH \t\tDate"<<endl;
	cout<<line<<endl;
	for (auto it = notPlayedMatches.begin(); it!= notPlayedMatches.end(); ++it){
		if(it->team1.name == s || it->team2.name == s){
			cout<<it->team1.name<<"\t"<<it->team2.name<<"\t"<<it->mainJudge.name<<"\t"<<it->helpJudge.name<<"\t"<<it->date.to_string()<<endl;
			cout<<dashedLine<<endl;
		}
	}
	cout<<dashedLine<<endl<<endl;
}

void League::printPointsTable(){
	sort(tms.begin(),tms.end(),[](const Team& t1, const Team& t2){return t1.points>t2.points;});
	cout<<"Team \t Points\n_______________\n"<<endl;
	for(auto el : tms){
		cout<<el.name<<" \t "<<el.points<<endl;
		cout<<"---------------"<<endl;
	}
	cout<<endl;
}
