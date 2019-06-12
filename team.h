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
	unsigned int points = 0;

	Team() = default;
	Team(std::string a, std::string b, std::string c, std::string d) : name(a), country(b), city(c), stadionName(d) {}

	bool operator==(const Team& t){
		return name==t.name  && city == t.city;
	}

	std::string to_string(){
		return name +"\t" +country +"\t" +city +"\t" +stadionName +"\t" +std::to_string(points) +"\n";
	}



};

#endif /* TEAM_H_ */
