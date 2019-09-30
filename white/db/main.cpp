#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.year != rhs.year) {
        return lhs.year < rhs.year;
    }
    if (lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    return lhs.day < rhs.day;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

ostream& operator<<(ostream& s, const Date& date) {
    s << setfill('0')
      << setw(4) << date.year << '-'
      << setw(2) << date.month << '-'
      << setw(2) << date.day;

    return s;
}

void skip_char(istream& s, const char ch) {
    if (s.peek() != ch) {
        throw exception();
    }
    s.ignore(1);
}

istream& operator>>(istream& s, Date& date) {
    s >> date.year;
    skip_char(s, '-');
    s >> date.month;
    skip_char(s, '-');
    s >> date.day;
    return s;
}

void parse_date(const string& input, Date& date) {
    istringstream s(input);

    try {
        s >> date;
    } catch (exception&) {
        throw runtime_error("Wrong date format: " + input);
    }

    if (date.month < 1 || date.month > 12) {
        stringstream message;
        message << "Month value is invalid: " << date.month;
        throw runtime_error(message.str());
    }

    if (date.day < 1 || date.day > 31) {
        stringstream message;
        message << "Day value is invalid: " << date.day;
        throw runtime_error(message.str());
    }
}

struct Record {
    Date date;
    string event;
};

bool operator<(const Record& lhs, const Record& rhs) {
    if (!(lhs.date == rhs.date)) {
        return lhs.date < rhs.date;
    }
    return lhs.event < rhs.event;
}

ostream& operator<<(ostream& s, const Record& record) {
    s << record.date << ' ' << record.event;

    return s;
}

istream& operator>>(istream& s, Record& record) {

    string input_date;

    s >> input_date;

    parse_date(input_date, record.date);

    s >> record.event;

    return s;
}

using EventsByDate = pair<Date, set<string>>;

ostream& operator<<(ostream& s, const EventsByDate& eventsByDate) {
    for (const auto& event: eventsByDate.second) {
        s << eventsByDate.first << ' ' << event << endl;
    }
    return s;
}


struct Db {
    map<Date, set<string>> eventByDate;


    void operator+=(const Record& record) {
        auto it = eventByDate.find(record.date);

        if (it == eventByDate.end()) {
            set<string> events {record.event};
            eventByDate.insert({record.date, events});
        } else {
            auto& records = it->second;
            records.insert(record.event);
        }
    }


    void operator-=(const Record& record) {
        auto it = eventByDate.find(record.date);
        if (it != eventByDate.end()) {
            auto& events = it->second;
            events.erase(record.event);
        }
    }

    void operator-=(const Date& date) {
        auto it = eventByDate.find(date);
        if (it != eventByDate.end()) {
            eventByDate.erase(it);
        }
    }

    void print_events(ostream& s, const Date& date) {
        auto it = eventByDate.find(date);
        if (it != eventByDate.end()) {
            s << *it;
        }
    }
};

ostream& operator<<(ostream& s, const Db& db) {
    for(const auto& byDate: db.eventByDate) {
        s << byDate;
    }

    return s;
}


void process_command(const string& params, Db& db) {
    stringstream params_stream(params);

    string command;
    params_stream >> command;

    if (command == "Add") {
        Record rec;
        params_stream >> rec;

        db += rec;
    } else  if (command == "Del") {
        Date date;
        params_stream >> date;
        string event;
        params_stream >> event;

        if (event.size() > 0) {
            db -= Record{date, event};
        } else {
            db -= date;
        }

    } else if (command == "Find") {
        Date date;
        params_stream >> date;

        db.print_events(cout, date);

    } else if (command == "Print") {
        cout << db;
    } else {
        throw runtime_error("Unknown command: " + command);
    }
}


int main()
{
    Db db;

    if (2 > 3U) {
        cout << "work" << endl;
    }

    while(true) {
        string command;
        getline(cin, command);
        try {
            process_command(command, db);
        } catch(exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
