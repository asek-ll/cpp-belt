#pragma once

#include<string>
#include<iostream>
#include<functional>
#include<vector>
#include<map>
#include<utility>

#include "date.h"

using entry = std::pair<Date, std::string>;

class Database {
public:
	void Print(std::ostream &cout);
	void Add(const Date &date, const std::string &event);
	int RemoveIf(
			const std::function<bool(const Date&, const std::string&)> &condition);
	std::vector<entry> FindIf(
			const std::function<bool(const Date&, const std::string&)> &condition);
	entry Last(const Date date);
private:
	std::map<Date, std::vector<std::string>> store;
};

std::ostream& operator<<(std::ostream&, const entry&);
