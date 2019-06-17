/*
 * league.h
 *
 *  Created on: Jun 4, 2019
 *      Author: Mersudin Hajdarević
 */

#ifndef LEAGUE_H_
#define LEAGUE_H_
#include "team.h"
#include "match.h"
#include "judges.h"
#include <iostream>
#include <vector>
#include <list>


class League{
private:
	std::string name;
	std::string country;
	std::vector <Team> tms;				// brz pristup el ( operator [] ), nema potrebe za brisanjem
	std::vector<Match> playedMatches;	// umjesto stack zbog potrebe prolaska kroz cijelu kolekciju
	std::list<Match> notPlayedMatches; // umjesto queue iz istog razloga

public:
	League();
	League(std::string, std::string);

	void generateMatches();
	void printNextScheduledMatch() const ;
	void printPlayedMatches();
	void printNotPlayedMatches();
	void cancelLastMatch();
	void printTeamPlayedMatches(const std::string&);
	void printTeamNotPlayedMatches(const std::string&);
	void printPointsTable();
	int indexOfTeam(const std::string&);
	int longestTeamName();
	int longestJudgeName();

	const std::string& getCountry() const;
	void setCountry(const std::string& country);
	const std::string& getName() const;
	void setName(const std::string& name);
	std::list<Match>& getNotPlayedMatches();
	void setNotPlayedMatches(std::list<Match>& notPlayedMatches);
	std::vector<Match>& getPlayedMatches();
	void setPlayedMatches(const std::vector<Match>& playedMatches);
	std::vector<Team>& getTms();
	void setTms(const std::vector<Team>& tms);
};

#endif /* LEAGUE_H_ */
