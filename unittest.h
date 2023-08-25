/*
 * unittest.h
 *
 *  Created on: 6 okt 2014
 *      Author: Mattias Larsson Sköld
 *      https://github.com/mls-m5/mls-unit-test
 */

#pragma once

#include "expect.h"
#include "registertest.h"
#include "unittestvars.h"

namespace unittest {

// Function to require semicolon after macro
inline void semicolon() {}

} // namespace unittest

#define TEST_SUIT_BEGIN(testName)                                              \
    struct TestSuit##testName : public unittest::StaticTestSuit {              \
        TestSuit##testName();                                                  \
    } TestSuit##testName##__instance;                                          \
    TestSuit##testName::TestSuit##testName() : unittest::StaticTestSuit{} {    \
        this->testSuitName = #testName;                                        \
        unittest::testResult = &this->testResult;

#define TEST_CASE(name)                                                        \
    ;                                                                          \
    newTest(name) = [this]() -> void

#define TEST_SUIT_END                                                          \
    ;                                                                          \
    }
