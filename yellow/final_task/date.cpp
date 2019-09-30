#include "date.h"

#include <iomanip>

using namespace std;

Date ParseDate(std::istream &is) {
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	return Date { year, month, day };
}

bool operator==(Date d1, Date d2) {
	return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
}
bool operator>(Date d1, Date d2) {
	if (d1.year == d2.year) {
		if (d1.month == d2.month) {
			return d1.day > d2.day;
		}
		return d1.month > d2.month;
	}
	return d1.year > d2.year;
}
bool operator<(Date d1, Date d2) {
	if (d1.year == d2.year) {
		if (d1.month == d2.month) {
			return d1.day < d2.day;
		}
		return d1.month < d2.month;
	}
	return d1.year < d2.year;
}
bool operator>=(Date d1, Date d2) {
	return !(d1 < d2);
}
bool operator<=(Date d1, Date d2) {
	return !(d1 > d2);
}
bool operator!=(Date d1, Date d2) {
	return !(d1 == d2);
}

ostream& operator<<(ostream &s, const Date &date) {
	s << setfill('0') << setw(4) << date.year << '-' << setw(2) << date.month
			<< '-' << setw(2) << date.day;

	return s;
}
