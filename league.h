/*
 * league.h
 *
 *  Created on: Jun 4, 2019
 *      Author: mersudin
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
public:
	std::string name;
	std::string country;
	std::vector <Team> tms;
	std::vector<Match> playedMatches;
	std::list<Match> notPlayedMatches;

	League();
	League(std::string, std::string);

	void generateMatches();
	void printNextScheduledMatch() const;
	void printPlayedMatches();
	void printNotPlayedMatches();
	void cancelLastMatch();
	void printTeamPlayedMatches(const std::string&);
	void printTeamNotPlayedMatches(const std::string&);
	void printPointsTable();
};

#endif /* LEAGUE_H_ */
