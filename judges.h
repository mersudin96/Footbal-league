/*
 * judges.h
 *
 *  Created on: Jun 4, 2019
 *      Author: mersudin
 */

#ifndef JUDGES_H_
#define JUDGES_H_
#include<iostream>

struct Judge{
	std::string name;
	std::string lastName;
	std::string country;

	Judge() = default;
	Judge(const Judge& o) : name(o.name), lastName(o.lastName), country(o.country) {}
	Judge(std::string n, std::string l) : name(n), lastName(l) {}
	Judge(std::string n, std::string l, std::string c) : name(n), lastName(l), country(c) {}

	bool operator==(const Judge& o){
		return (name == o.name && lastName == o.lastName && o.country == country);
	}
};

#endif /* JUDGES_H_ */
