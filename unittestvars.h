#pragma once

namespace unittest {

//! If testResult is not 0 the current test has failed
inline int *testResult = 0;
extern const char *testFileName;
inline bool shouldCatchExceptions = true;

//! Mark the test as failed
inline void failTest() {
    ++(*testResult);
}

} // namespace unittest
