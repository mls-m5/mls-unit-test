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
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace unittest {

using testFunction = std::function<void()>;

extern std::map<std::string, testFunction> testMap;

namespace {

std::map<std::string, std::string> testResults;
std::function<void()> setup;

} // namespace

void initTests();

//! Check which tests should be used or list tests
inline int parseArguments(int argc, char **argv) {
    // Let the user choose test from command line
    if (argc > 1) {
        if (std::string(argv[1]) == "-l") {
            std::cout << "available tests:" << std::endl;
            for (auto it : testMap) {
                std::cout << it.first << std::endl;
            }
            return 0;
        }

        auto tmpMap = std::move(testMap);
        for (auto i = 1; i < argc; ++i) {
            auto f = tmpMap.find(argv[i]);
            if (f != tmpMap.end()) {
                auto testName = argv[i];
                testMap[testName] = f->second;
            }
        }
    }

    return 1;
}

#if 0
//! The main function used for running all the tests
inline int runTests(int argc, char **argv) {
    using std::cout;
    using std::endl;
    int numFailed = 0;
    int numSucceded = 0;
    int numInactive = 0;

    if (!parseArguments(argc, argv)) {
        return 0;
    }

    if (setup) {
        setup();
    }

    cout << "==== Starts test suit " << testFileName << " ====" << endl << endl;

    for (auto it : testMap) {
        if (it.first.rfind("disabled ", 0) == 0) {
            testResults[it.first] = "disabled";
            ++numInactive;
            continue;
        }

        cout << "=== running test: " << it.first << " ===" << endl;
        testResult = 0;

#ifdef DO_NOT_CATCH_ERRORS
        it.second();
#else
        try {
            it.second();
        }
        catch (std::exception &e) {
            std::cerr << "error: " << e.what() << endl;
            testResult = -2;
        }
        catch (const char *c) {
            std::cerr << "error: " << c << endl;
            testResult = -2;
        }
        catch (const std::string &what) {
            std::cerr << "error: " << what << endl;
            testResult = -2;
        }
        catch (...) {
            std::cerr << "error" << endl;
            testResult = -2;
        }
#endif
        if (testResult == -1) {
            cout << " --> not impl" << endl << endl;
            testResults[it.first] = "not implemented";
        }
        if (testResult == -2) {
            cout << " --> crashed" << endl << endl;
            ++numFailed;
            testResults[it.first] = "crashed!";
        }
        else if (testResult) {
            cout << " --> failed" << endl << endl << endl << endl;
            numFailed++;
            testResults[it.first] = "fail";
        }
        else {
            cout << " --> success " << endl << endl << endl << endl;
            testResults[it.first] = "pass";
            numSucceded++;
        }
    }

    cout << endl;
    cout << "==== results: ===============================" << endl;
    for (auto it : testResults) {
        cout << it.second;
        for (int i = it.second.size(); i < 15; ++i) {
            cout << " ";
        }
        if (it.first.rfind("disabled ", 0) == 0) {
            cout << " " << it.first.substr(9) << "\n";
        }
        else {
            cout << " " << it.first << "\n";
        }
    }
    cout << endl;
    if (numFailed) {
        cout << "TEST FAILED...";
    }
    else {
        cout << "SUCCESS...";
    }
    cout << "\n";
    if (numInactive) {
        cout << "(Disabled: " << numInactive << ") ";
    }
    cout << "Failed: " << numFailed << " Passed: " << numSucceded << endl;

    return numFailed > 0;
}
#endif

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

// #define TEST_SUIT_BEGIN
//     std::map<std::string, unittest::testFunction> unittest::testMap;
//     int unittest::testResult;
//     const char *unittest::testFileName = __FILE__;
//     void unittest::initTests() {
//         unittest::semicolon()

#define TEST_CASE(name)                                                        \
    ;                                                                          \
    newTest(name) = [this]() -> void

#define TEST_SUIT_END                                                          \
    ;                                                                          \
    }

// #define TEST_SUIT_END
//     ;
//     }
//     int main(int argc, char **argv) {
//         unittest::initTests();
//         return unittest::runTests(argc, argv);
//     }

#define SETUP                                                                  \
    ;                                                                          \
    unittest::setup = []() -> void
