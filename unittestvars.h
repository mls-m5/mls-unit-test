#pragma once

#include <map>

namespace unittest {

//! If testResult is not 0 the current test has failed
inline int *testResult = nullptr;
extern const char *testFileName;

//! Mark the test as failed
inline void failTest() {
    ++testResult;
}

} // namespace unittest
