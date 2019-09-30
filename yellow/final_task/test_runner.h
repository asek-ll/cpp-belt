#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <vector>

template<class T>
std::ostream& operator <<(std::ostream &os, const std::vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

void Assert(const bool cond, const std::string &message);

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const std::string &test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::runtime_error &e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " unit tests failed. Terminate"
					<< std::endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};
