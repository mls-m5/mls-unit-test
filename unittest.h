/*
 * unittest.h
 *
 *  Created on: 6 okt 2014
 *      Author: Mattias Larsson Sköld
 *      https://github.com/mls-m5/mls-unit-test
 */


#pragma once

#include <iostream>
#include <map>
#include <string>

typedef void (*testFunction)();

extern std::map<std::string, testFunction> testMap;
extern int test_result;
extern const char *test_file_name;
static std::map<std::string, std::string> test_results;

inline int runTests(int argc, char **argv) {
    using std::cout;
    using std::endl;
    int numFailed = 0;
    int numSucceded = 0;

    // Let the user choose test from command line
    if (argc > 1) {
        if (std::string(argv[1]) == "-l") {
            cout << "available tests:" << endl;
            for (auto it : testMap) {
                cout << it.first << endl;
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

    cout << "==== Starts test suit " << test_file_name << " ====" << endl
         << endl;

    for (auto it : testMap) {
        cout << "=== running test: " << it.first << " ===" << endl;
        test_result = 0;

#ifdef DO_NOT_CATCH_ERRORS
        it.second();
#else
        try {
            it.second();
        }
        catch (std::exception &e) {
            std::cerr << "error: " << e.what() << endl;
            test_result = -2;
        }
        catch (const char *c) {
            std::cerr << "error: " << c << endl;
            test_result = -2;
        }
        catch (const std::string &what) {
            std::cerr << "error: " << what << endl;
            test_result = -2;
        }
        catch (...) {
            std::cerr << "error" << endl;
            test_result = -2;
        }
#endif
        if (test_result == -1) {
            cout << " --> not impl" << endl << endl;
            test_results[it.first] = "not implemented";
        }
        if (test_result == -2) {
            cout << " --> crashed" << endl << endl;
            test_results[it.first] = "crashed!";
        }
        else if (test_result) {
            cout << " --> failed" << endl << endl << endl << endl;
            numFailed++;
            test_results[it.first] = "failed";
        }
        else {
            cout << " --> success " << endl << endl << endl << endl;
            test_results[it.first] = "succeded";
            numSucceded++;
        }
    }

    cout << endl;
    cout << "==== results: ===============================" << endl;
    for (auto it : test_results) {
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

#define TEST_SUIT_BEGIN                                                        \
    std::map<std::string, testFunction> testMap;                               \
    int test_result;                                                           \
    const char *test_file_name = __FILE__;                                     \
    void initTests() {                                                         \
        do {                                                                   \
        } while (false)


// Remember to return 0 on success!!!
#define TEST_CASE(name)                                                        \
    ;                                                                          \
    testMap[name] = []() -> void

#define TEST_SUIT_END                                                          \
    ;                                                                          \
    }                                                                          \
    int main(int argc, char **argv) {                                          \
        initTests();                                                           \
        return runTests(argc, argv);                                           \
    }

#define PRINT_INFO std::cout << __FILE__ << ":" << __LINE__ << ": ";
#define ASSERT(x, error)                                                       \
    if (!(x)) {                                                                \
        PRINT_INFO;                                                            \
        test_result++;                                                         \
        std::cout << #x << ": " << error << std::endl;                         \
        return;                                                                \
    }

#define EXPECT(x) ASSERT(x, "expression is not true")

#define ASSERT_EQ(x, y)                                                        \
    if (!((x) == (y))) {                                                       \
        PRINT_INFO;                                                            \
        test_result++;                                                         \
        std::cout << #x << " = " << x << " is not equal to " << #y << " = "    \
                  << y << std::endl;                                           \
        test_result++;                                                         \
        return;                                                                \
    }
#define ASSERT_NE(x, y)                                                        \
    if (((x) == (y))) {                                                        \
        PRINT_INFO;                                                            \
        std::cout << #x << " = " << x << " is equal to " << #y << " = " << y   \
                  << std::endl;                                                \
        test_result++;                                                         \
        return;                                                                \
    }

#define ASSERT_GT(x, y)                                                        \
    if (!((x) > (y))) {                                                        \
        PRINT_INFO;                                                            \
        std::cout << #x << " = " << x << " is not greater than " << #y         \
                  << " = " << y << std::endl;                                  \
        test_result++;                                                         \
        return;                                                                \
    }

#define ASSERT_LT(x, y)                                                        \
    if (!((x) < (y))) {                                                        \
        PRINT_INFO;                                                            \
        std::cout << #x << " = " << x << " is not less than " << #y << " = "   \
                  << y << std::endl;                                           \
        test_result++;                                                         \
        return;                                                                \
    }

#define ASSERT_NEAR(x, y, e)                                                   \
    {                                                                          \
        auto a = (x);                                                          \
        auto b = (y);                                                          \
        if (a + e < b || a > b + e) {                                          \
            PRINT_INFO;                                                        \
            std::cout << #x << " is not near " << #y << std::endl;             \
            ++test_result;                                                     \
        }                                                                      \
    }


#define ERROR(error)                                                           \
    PRINT_INFO;                                                                \
    std::cout << error << std::endl;                                           \
    test_result++;                                                             \
    return;

// The not implemented error is used to flag for wanted features not implemented
#define ERROR_NOT_IMPLEMENTED()                                                \
    PRINT_INFO;                                                                \
    std::cout << "not implemented" << std::endl;                               \
    test_result = -1;                                                          \
    return;
