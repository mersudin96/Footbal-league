#include "league.h"
#include <iostream>
#include <algorithm>
#include <exception>
using namespace std;

extern vector <Team> teams;
extern vector <Judge> judges;

string dashedLine(70, '-');
string line(70, '_');
string longerDashedLine(85, '-');
string longerLine(85, '_');


League::League() { tms = teams; }
League::League(string n, string c) : name(n), country(c){
	for(size_t i=0; i<teams.size(); ++i){
		if(teams[i].country == country)
			tms.push_back(teams[i]);
	}
	generateMatches();
}

void League::generateMatches(){
	if(!judges.size())
		throw string("Zovi sudca inače ti neće imat ko sudit.");
	int judgesFromSameCountry = 0;
	for(size_t i=0; i<judges.size(); ++i){
		if(judges[i].country == country)
			judgesFromSameCountry++;
	}
	if(judgesFromSameCountry<2)
		throw string("Trebo bi razmislit da zovneš kojeg sudca iz druge države...");

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
	if(notPlayedMatches.size()){
		Match m = notPlayedMatches.front();
		int sizeT1 = (m.team1.name.size() < 6) ? 6 : m.team1.name.size();
		int sizeT2 = (m.team2.name.size() < 6) ? 6 : m.team2.name.size();
		int sizeMJ = (m.mainJudge.name.size()) < 6 ? 6 : m.mainJudge.name.size();
		int sizeHJ = (m.helpJudge.name.size() < 6) ? 6 : m.helpJudge.name.size();
		string s = "    ";
		string s1(sizeT1+s.size()-5, ' ');
		string s2(sizeT2+s.size()-5, ' ');
		string s3(sizeMJ+s.size()-5, ' ');
		string s4(sizeHJ+s.size()-5, ' ');

		cout<<"\n\nTeam1"<<s1<<"Team2"<<s2<<"Judge"<<s3<<"Judge2"<<s4<<"Date\n"<<line<<endl<<endl;
		cout<<m.team1.name<<s<<m.team2.name<<s<<m.mainJudge.name<<s<<m.helpJudge.name<<s<<m.date.day<<"."<<m.date.month<<"."<<m.date.year<<endl;
		cout<<dashedLine<<endl<<dashedLine<<endl;
	}else{
		throw string("None matches are scheduled...");
	}
}

void League::printPlayedMatches(){
	string spaceLT(longestTeamName(), ' ');
	string spaceLJ(longestJudgeName(), ' ');
	string s = "   ";
	spaceLT += s;
	spaceLJ += s;

	string spaceTitleT1T2(spaceLT.size()-5+s.size(), ' ');
	string spaceTitleT2J(spaceLT.size()-5, ' ');
	string spaceTitleJD(spaceLJ.size()-5, ' ');

	string title = "\n\nTeam1" + spaceTitleT1T2 +"Team2" + spaceTitleT2J +"Judge" +spaceTitleJD +"Date\tResult\n";
	cout<<title<<line<<endl<<endl;

	for(size_t i=0; i<playedMatches.size(); ++i){
		string spaceT1T2(spaceLT.size()-playedMatches[i].team1.name.size() + s.size(), ' ');
		string spaceT2J(longestTeamName()-playedMatches[i].team2.name.size()+s.size(), ' ');
		string spaceJD(longestJudgeName()-playedMatches[i].mainJudge.name.size()+s.size(), ' ');
		cout<<playedMatches[i].team1.name<<spaceT1T2<<playedMatches[i].team2.name<<spaceT2J<<playedMatches[i].mainJudge.name<<spaceJD
				<<playedMatches[i].date.to_string()<<"\t"<<playedMatches[i].result.first<<":"<<playedMatches[i].result.second<<endl;
		cout<<dashedLine<<endl;
	}
	cout<<dashedLine<<endl;
}

void League::printNotPlayedMatches(){
	string spaceLT(longestTeamName(), ' ');
	string spaceLJ(longestJudgeName(), ' ');
	string s = "   ";
	spaceLT += s;
	spaceLJ += s;

	string spaceTitleT1T2(spaceLT.size()-5+s.size(), ' ');
	string spaceTitleT2J(spaceLT.size()-5, ' ');
	string spaceTitleJD(spaceLJ.size()-5, ' ');

	string title = "\n\nTeam1" + spaceTitleT1T2 +"Team2" + spaceTitleT2J +"Judge" +spaceTitleJD +"Date\n";
	cout<<title<<line<<endl<<endl;

	for (auto it = notPlayedMatches.begin(); it!= notPlayedMatches.end(); ++it){
		string spaceT1T2(spaceLT.size()-it->team1.name.size() + s.size(), ' ');
		string spaceT2J(longestTeamName()-it->team2.name.size()+s.size(), ' ');
		string spaceJD(longestJudgeName()-it->mainJudge.name.size()+s.size(), ' ');
		cout<<it->team1.name<<spaceT1T2<<it->team2.name<<spaceT2J<<it->mainJudge.name<<spaceJD<<it->date.to_string()<<endl;
		cout<<dashedLine<<endl;
	}
	cout<<dashedLine<<endl;
}

void League::cancelLastMatch(){
	if(playedMatches.size()){
		Match a = playedMatches[playedMatches.size()-1];
		int index;
		if(a.result.first>a.result.second){
			index = indexOfTeam(a.team1.name);
			tms[index].removePoints(3);
		}
		else{
			index = indexOfTeam(a.team2.name);
			tms[index].removePoints(3);
		}
		a.result.first=0;
		a.result.second=0;
		notPlayedMatches.push_front(a);
		playedMatches.pop_back();
		cout<<"Match "<<a.team1.name<<" vs "<<a.team2.name<<" has been canceled"<<endl<<endl;
	}else
		cout<<"No match yet played!"<<endl<<endl;
}

void League::printTeamPlayedMatches(const string& c){
	cout<<"\n\t\t**Played matches** \n\t       ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ \n";

	string spaceLT(longestTeamName(), ' ');
	string spaceLJ(longestJudgeName(), ' ');
	string s = "   ";
	spaceLT += s;
	spaceLJ += s;

	string spaceTitleT1T2(spaceLT.size()-5+s.size(), ' ');
	string spaceTitleT2J(spaceLT.size()-5, ' ');
	string spaceTitleJD(spaceLJ.size()-5, ' ');
	string title = "\n\nTeam1" + spaceTitleT1T2 +"Team2" + spaceTitleT2J +"Judge" +spaceTitleJD+"Judge2" +spaceTitleJD +"Date\tResult\n";
	cout<<title<<longerLine<<endl<<endl;

	for (size_t i=0; i<playedMatches.size(); ++i){
		if(playedMatches[i].team1.name == c || playedMatches[i].team2.name == c){
			string spaceT1T2(spaceLT.size()-playedMatches[i].team1.name.size() + s.size(), ' ');
			string spaceT2J(longestTeamName()-playedMatches[i].team2.name.size()+s.size(), ' ');
			string spaceJD(longestJudgeName()-playedMatches[i].mainJudge.name.size()+s.size(), ' ');
			string spaceHJ(longestJudgeName()-playedMatches[i].helpJudge.name.size()+s.size(), ' ');
			cout<<playedMatches[i].team1.name<<spaceT1T2<<playedMatches[i].team2.name<<spaceT2J<<playedMatches[i].mainJudge.name<<spaceJD
					<<playedMatches[i].helpJudge.name<<spaceHJ<<playedMatches[i].date.to_string()<<"\t "<<
					playedMatches[i].result.first<<":"<<playedMatches[i].result.second<<endl;
			cout<<longerDashedLine<<endl;
		}
	}
	cout<<longerDashedLine<<endl<<endl;
}

void League::printTeamNotPlayedMatches(const string& c){
	cout<<"\n\t    **Not played mathces** \n\t   ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ \n";

	string spaceLT(longestTeamName(), ' ');
	string spaceLJ(longestJudgeName(), ' ');
	string s = "   ";
	spaceLT += s;
	spaceLJ += s;

	string spaceTitleT1T2(spaceLT.size()-5+s.size(), ' ');
	string spaceTitleT2J(spaceLT.size()-5, ' ');
	string spaceTitleJD(spaceLJ.size()-5, ' ');
	string title = "\n\nTeam1" + spaceTitleT1T2 +"Team2" + spaceTitleT2J +"Judge" +spaceTitleJD +"\tJudge2 \tDate\n";
	cout<<title<<line<<endl<<endl;

	for (auto it = notPlayedMatches.begin(); it!= notPlayedMatches.end(); ++it){
		if(it->team1.name == c || it->team2.name == c){
			string spaceT1T2(spaceLT.size()-it->team1.name.size() + s.size(), ' ');
			string spaceT2J(longestTeamName()-it->team2.name.size()+s.size(), ' ');
			string spaceJD(longestJudgeName()-it->mainJudge.name.size()+s.size(), ' ');
			string spaceHJ(longestJudgeName()-it->helpJudge.name.size()+s.size(), ' ');
			cout<<it->team1.name<<spaceT1T2<<it->team2.name<<spaceT2J<<it->mainJudge.name<<spaceJD<<it->helpJudge.name<<spaceHJ<<it->date.to_string()<<endl;
			cout<<dashedLine<<endl;
		}
	}
	cout<<dashedLine<<endl<<endl;
}

void League::printPointsTable(){
	sort(tms.begin(),tms.end(),[](const Team& t1, const Team& t2){return t1.points>t2.points;});
	cout<<"Team\t\tPoints\n______________________\n"<<endl;
	for(auto el : tms){
		cout<<el.name<<"\t\t"<<el.points<<endl;
		cout<<"----------------------"<<endl;
	}
	cout<<endl;
}

int League::longestTeamName(){
	unsigned int max = 0;
	for(size_t i=0; i<tms.size(); ++i){
		if(tms[i].name.size()>max)
			max = tms[i].name.size();
	}
	if (max<6) max = 6;
	return max;
}

int League::longestJudgeName(){
	unsigned int max = 0;
	for(size_t i=0; i<judges.size(); ++i){
		if(judges[i].name.size()>max)
			max = judges[i].name.size();
	}
	if (max<6) max = 6;
	return max;
}

int League::indexOfTeam(const string& s){
	for(size_t i = 0; i<tms.size(); ++i){
		if(tms[i].name == s)
			return i;
	}
	return -1;
}


const std::string& League::getCountry() const {
		return country;
}

void League::setCountry(const std::string& country) {
	this->country = country;
}

const std::string& League::getName() const {
	return name;
}

void League::setName(const std::string& name) {
	this->name = name;
}

std::list<Match>& League::getNotPlayedMatches(){
	return notPlayedMatches;
}

void League::setNotPlayedMatches(std::list<Match>& notPlayedMatches) {
	this->notPlayedMatches = notPlayedMatches;
}

std::vector<Match>& League::getPlayedMatches() {
	return playedMatches;
}

void League::setPlayedMatches(const std::vector<Match>& playedMatches) {
	this->playedMatches = playedMatches;
}

std::vector<Team>& League::getTms(){
	return tms;
}

void League::setTms(const std::vector<Team>& tms) {
	this->tms = tms;
}
