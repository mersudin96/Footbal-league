/*
 * match.h
 *
 *  Created on: Jun 4, 2019
 *      Author: mersudin
 */

#ifndef MATCH_H_
#define MATCH_H_
#include "date.h"
#include "team.h"
#include "judges.h"
#include <iostream>


struct Match{
	Team team1;
	Team team2;
	Judge mainJudge;
	Judge helpJudge;
	Date date;
	//std::string result;
	std::pair<int,int> result;

	Match() = default;
	Match(const Match& o) : team1(o.team1), team2(o.team2), mainJudge(o.mainJudge), helpJudge(o.helpJudge), date(o.date), result(o.result) {}
	Match(Team t1, Team t2, Judge j1, Judge j2, Date d) : team1(t1), team2(t2), mainJudge(j1), helpJudge(j2), date(d){}
};

#endif /* MATCH_H_ */
