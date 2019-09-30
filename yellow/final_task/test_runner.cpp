#include "test_runner.h"

void Assert(bool cond, const std::string &message) {
	AssertEqual(cond, true, message);
}
