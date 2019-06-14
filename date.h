/*
 * date.h
 *
 *  Created on: Jun 5, 2019
 *      Author: mersudin
 */

#ifndef DATE_H_
#define DATE_H_
#include <iostream>
#include <string>

struct Date{
	unsigned int day;
	unsigned int month;
	unsigned int year;

	Date() : day(1), month(1), year(2000) {}
	Date(const Date& o) : day(o.day), month(o.month), year(o.year) {}
	Date(unsigned int d, unsigned int m, unsigned int y) : day(d), month(m), year(y) {}

	std::string to_string(){
		return std::to_string(day) +"." +std::to_string(month) +"." +std::to_string(year);
	}
};


#endif /* DATE_H_ */
