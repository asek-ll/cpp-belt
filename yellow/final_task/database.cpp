#include "database.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

void Database::Print(ostream &cout) {
	for (const auto &pair : store) {
		for (const auto &event : pair.second) {
			cout << pair.first << " " << event << endl;
		}
	}
}

void Database::Add(const Date &date, const string &event) {
	auto it = store.find(date);
	if (it == store.end()) {
		vector<string> events { event };
		store.insert( { date, events });
	} else {
		auto event_it = find(it->second.begin(), it->second.end(), event);
		if (event_it == it->second.end()) {
			it->second.push_back(event);
		}
	}
}
int Database::RemoveIf(
		const function<bool(const Date&, const string&)> &condition) {
	int removed = 0;
	for (auto it = store.begin(); it != store.end(); ++it) {
		Date date = it->first;
		auto new_end = remove_if(it->second.begin(), it->second.end(),
				[condition, date](string &event) {
					return condition(date, event);
				});
		removed += (it->second.end() - new_end);
		it->second.erase(new_end, it->second.end());
		if (it->second.empty()) {
			store.erase(it);
		}
	}
	return removed;
}

vector<entry> Database::FindIf(
		const std::function<bool(const Date&, const std::string&)> &condition) {
	vector<entry> result;
	for (const auto &pair : store) {
		for (const auto &event : pair.second) {
			if (condition(pair.first, event)) {
				result.push_back( { pair.first, event });
			}
		}
	}
	return result;
}

entry Database::Last(const Date date) {
	auto it = find_if(store.rbegin(), store.rend(), [date](const auto &pair) {
		return pair.first <= date;
	});

	if (it == store.rend()) {
		throw invalid_argument("No");
	}

	return {it->first, it->second.back()};
}

ostream& operator<<(ostream &s, const entry &pair) {
	s << pair.first << " '" << pair.second << "'";

	return s;
}
