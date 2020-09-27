#pragma once

#include <map>

namespace unittest {

//! If testResult is not 0 the current test has failed
extern int testResult;
extern const char *testFileName;

void failTest() {
    ++testResult;
}

} // namespace unittest
