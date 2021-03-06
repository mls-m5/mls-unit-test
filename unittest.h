/*
 * unittest.h
 *
 *  Created on: 6 okt 2014
 *      Author: Mattias Larsson Sköld
 *      https://github.com/mls-m5/mls-unit-test
 */

#pragma once

#include "unittestvars.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace unittest {

typedef void (*testFunction)();

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

//! The main function used for running all the tests
inline int runTests(int argc, char **argv) {
    using std::cout;
    using std::endl;
    int numFailed = 0;
    int numSucceded = 0;

    if (!parseArguments(argc, argv)) {
        return 0;
    }

    if (setup) {
        setup();
    }

    cout << "==== Starts test suit " << testFileName << " ====" << endl << endl;

    for (auto it : testMap) {
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
            testResults[it.first] = "failed";
        }
        else {
            cout << " --> success " << endl << endl << endl << endl;
            testResults[it.first] = "succeded";
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
        cout << " " << it.first << endl;
    }
    cout << endl;
    if (numFailed) {
        cout << "TEST FAILED...";
    }
    else {
        cout << "SUCCESS...";
    }
    cout << endl;
    cout << "Failed: " << numFailed << " Succeded: " << numSucceded << endl;

    return numFailed > 0;
}

// Function to require semicolon after macro
inline void semicolon(){};

} // namespace unittest

#define TEST_SUIT_BEGIN                                                        \
    std::map<std::string, unittest::testFunction> unittest::testMap;           \
    int unittest::testResult;                                                  \
    const char *unittest::testFileName = __FILE__;                             \
    void unittest::initTests() {                                               \
        unittest::semicolon()

#define TEST_CASE(name)                                                        \
    ;                                                                          \
    unittest::testMap[name] = []() -> void

#define TEST_SUIT_END                                                          \
    ;                                                                          \
    }                                                                          \
    int main(int argc, char **argv) {                                          \
        unittest::initTests();                                                 \
        return unittest::runTests(argc, argv);                                 \
    }

#define SETUP                                                                  \
    ;                                                                          \
    unittest::setup = []() -> void

//! -------------- Asserts and tests -----------------------------------

#define PRINT_INFO std::cout << __FILE__ << ":" << __LINE__ << ": ";
#define ASSERT(test_var_x, error)                                              \
    if (!(test_var_x)) {                                                       \
        PRINT_INFO;                                                            \
        testResult++;                                                          \
        std::cout << #test_var_x << ": " << error << std::endl;                \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT(test_var_x) ASSERT(test_var_x, "expression is not true")

// Support old syntax
#define ASSERT_EQ EXPECT_EQ
#define ASSERT_NE EXPECT_NE
#define ASSERT_GT EXPECT_GT
#define ASSERT_LT EXPECT_LT
#define ASSERT_NEAR EXPECT_LT

#define EXPECT_EQ(test_var_x, test_var_y)                                      \
    if (!((test_var_x) == (test_var_y))) {                                     \
        PRINT_INFO;                                                            \
        testResult++;                                                          \
        std::cout << #test_var_x << " = '" << test_var_x                       \
                  << "' is not equal to " << #test_var_y << " = '"             \
                  << test_var_y << "'" << std::endl;                           \
        testResult++;                                                          \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_NE(test_var_x, test_var_y)                                      \
    if ((test_var_x) == (test_var_y)) {                                        \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x << " is equal to "     \
                  << #test_var_y << " = " << test_var_y << std::endl;          \
        testResult++;                                                          \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_GT(test_var_x, test_var_y)                                      \
    if (!((test_var_x) > (test_var_y))) {                                      \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x                        \
                  << " is not greater than " << #test_var_y << " = "           \
                  << test_var_y << std::endl;                                  \
        testResult++;                                                          \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_LT(test_var_x, test_var_y)                                      \
    if (!((test_var_x) < (test_var_y))) {                                      \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x                        \
                  << " is not less than " << #test_var_y << " = "              \
                  << test_var_y << std::endl;                                  \
        testResult++;                                                          \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_NEAR(test_var_x, test_var_y, test_var_e)                        \
    {                                                                          \
        auto a = (test_var_x);                                                 \
        auto b = (test_var_y);                                                 \
        if (a + test_var_e < b || a > b + test_var_e) {                        \
            PRINT_INFO;                                                        \
            std::cout << #test_var_x << " == " << test_var_x                   \
                      << " is not near " << #test_var_y << std::endl;          \
            ++testResult;                                                      \
        }                                                                      \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_TRUE(expression)                                                \
    {                                                                          \
        auto test_var_x = static_cast<bool>(expression);                       \
        if (!test_var_x) {                                                     \
            PRINT_INFO;                                                        \
            std::cout << #expression << " == " << test_var_x                   \
                      << " is not true as expected " << std::endl;             \
            ++testResult;                                                      \
        }                                                                      \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_FALSE(expression)                                               \
    {                                                                          \
        auto test_var_x = static_cast<bool>(expression);                       \
        if (test_var_x) {                                                      \
            PRINT_INFO;                                                        \
            std::cout << #expression << " == " << test_var_x                   \
                      << " is not false as expected " << std::endl;            \
            ++testResult;                                                      \
        }                                                                      \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_THROW(expression, error)                                        \
    {                                                                          \
        bool threw = false;                                                    \
        try {                                                                  \
            expression;                                                        \
        }                                                                      \
        catch (error & e) {                                                    \
            threw = true;                                                      \
        }                                                                      \
        if (!threw) {                                                          \
            std::cout << "Expected exeption " << #error << ": got none"        \
                      << std::endl;                                            \
            testResult++;                                                      \
            return;                                                            \
        }                                                                      \
    }                                                                          \
    unittest::semicolon()

#define ERROR(error)                                                           \
    PRINT_INFO;                                                                \
    std::cout << error << std::endl;                                           \
    testResult++;                                                              \
    return;                                                                    \
    unittest::semicolon()

// The not implemented error is used to flag for wanted features not implemented
#define ERROR_NOT_IMPLEMENTED()                                                \
    PRINT_INFO;                                                                \
    std::cout << "not implemented" << std::endl;                               \
    testResult = -1;                                                           \
    return;                                                                    \
    unittest::semicolon()
