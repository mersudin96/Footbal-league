/*
 * team.h
 *
 *  Created on: Jun 4, 2019
 *      Author: mersudin
 */
#ifndef TEAM_H_
#define TEAM_H_
#include<iostream>
#include<string>

struct Team{
	std::string name;
	std::string country;
	std::string city;
	std::string stadionName;
	int points;

	Team() : points(0) {}
	Team(const Team& o) : name(o.name), country(o.country), city(o.city), stadionName(o.stadionName), points(o.points) {}
	Team(std::string a, std::string b, std::string c, std::string d) : name(a), country(b), city(c), stadionName(d), points(0) {}

	bool operator==(const Team& t) const {
		return name==t.name  && city == t.city;
	}

	std::string to_string() const {
		return name +"\t" +country +"\t" +city +"\t" +stadionName +"\t" +std::to_string(points) +"\n";
	}

	void addPoints(int points) {
		this->points += points;
	}

	void removePoints(int points){
		this->points -=points;
	}
};
#endif /* TEAM_H_ */
