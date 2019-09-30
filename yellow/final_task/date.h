#pragma once

#include<istream>

struct Date {
	int year;
	int month;
	int day;
};

bool operator==(Date, Date);
bool operator>(Date, Date);
bool operator>=(Date, Date);
bool operator<(Date, Date);
bool operator<=(Date, Date);
bool operator!=(Date, Date);

std::ostream& operator<<(std::ostream&, const Date&);

Date ParseDate(std::istream &is);
