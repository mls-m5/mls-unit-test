#pragma once

#include "unittestvars.h"
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>

namespace unittest {

struct StaticTestSuit;

struct Tests {

    Tests() = default;
    Tests(const Tests &) = delete;
    Tests(Tests &&) = delete;
    Tests &operator=(const Tests &) = delete;
    Tests &operator=(Tests &&) = delete;
    ~Tests();

    static Tests &instance() {
        static Tests reg{};
        return reg;
    }

    int run(int argc, char **argv);

    //! Check which tests should be used or list tests
    int parseArguments(int argc, char **argv);

    std::vector<StaticTestSuit *> tests;
};

struct StaticTestSuit {
    StaticTestSuit() {
        Tests::instance().tests.push_back(this);
    }

    struct TestEntry {
        std::string suit;
        std::string name;
        std::function<void()> f = {};
        std::string result = {};
        bool isEnabled = true;
    };

    /// List instead of vector to keep position in memory
    std::list<TestEntry> entries;

    std::string testSuitName;
    int testResult = 0;

    int numFailed = 0;
    int numSucceded = 0;
    int numInactive = 0;

    bool isEnabled = true;

    std::function<void()> &newTest(std::string testName) {
        return add(testSuitName, testName);
    }

    std::function<void()> &add(std::string_view suitName,
                               std::string_view testName) {
        entries.push_back({
            .suit = std::string{suitName},
            .name = std::string{testName},
        });
        return entries.back().f;
    }

    int run(std::vector<std::string_view> enabledTests) {
        unittest::testResult = &testResult;
        //        using unittest::testResult;

        using std::cout;
        using std::endl;

        if (!enabledTests.empty()) {
            //            for (auto it = entries.begin(); it != entries.end();
            //            ++it) {
            for (auto &entry : entries) {
                //                auto &entry = *it;
                entry.isEnabled = false;
                for (auto &name : enabledTests) {
                    if (entry.name.find(name) != std::string::npos) {
                        entry.isEnabled = true;
                        break;
                    }
                }

                //                if (isEnabled) {
                //                    ++it;
                //                }
                //                else {
                //                    it = entries.erase(it);
                //                }
            }
        }

        cout << "==== Starts test suit " << testSuitName << " ====" << endl
             << endl;

        for (auto &it : entries) {
            if (!it.isEnabled || it.name.rfind("disabled ", 0) == 0) {
                it.result = "disabled";
                //                it.result = "disabled";
                ++numInactive;
                continue;
            }

            cout << "=== running test: " << it.name << " ===" << endl;
            testResult = 0;

            if (!shouldCatchExceptions) {
                it.f();
            }
            else {
                try {
                    it.f();
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
            }
            if (testResult == -1) {
                cout << " --> not impl" << endl << endl;
                it.result = "not implemented";
            }
            if (testResult == -2) {
                cout << " --> crashed" << endl << endl;
                ++numFailed;
                it.result = "crashed!";
            }
            else if (testResult) {
                cout << " --> failed" << endl << endl << endl << endl;
                numFailed++;
                it.result = "fail";
            }
            else {
                cout << " --> success " << endl << endl << endl << endl;
                it.result = "pass";
                numSucceded++;
            }
        }

        cout << endl;
        cout << "==== results: ===============================" << endl;
        for (auto &it : entries) {
            cout << it.result;
            for (auto i = it.result.size(); i < 15; ++i) {
                cout << " ";
            }
            if (it.name.rfind("disabled ", 0) == 0) {
                cout << " " << it.name.substr(9) << "\n";
            }
            else {
                cout << " " << it.name << "\n";
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
};

inline Tests::~Tests() = default;

inline int Tests::run(int argc, char **argv) {
    parseArguments(argc, argv);
    for (auto &test : tests) {
        if (test->isEnabled) {
            test->run({});
        }
    }

    if (tests.size() <= 1) {
        if (tests.size() == 1) {
            return tests.front()->numFailed;
        }
        return 0;
    }

    std::cout << "\n\n ====== Tests summary: ===============\n";

    int ret = 0;

    int numFailedSuits = 0;

    for (auto &test : tests) {
        if (!test->isEnabled) {
            std::cout << std::setw(30) << std::left << test->testSuitName;
            std::cout << std::setw(8) << std::left << "skipped\n";
            continue;
        }
        if (test->numFailed > 0) {
            ret = -1;
            ++numFailedSuits;
        }
        std::cout << std::setw(30) << std::left << test->testSuitName;
        std::cout << std::setw(8) << std::left
                  << ((test->numFailed > 0) ? "failed" : "passed");
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << numFailedSuits << " of " << tests.size()
              << " test suits failed failed \n";

    std::cout.flush();

    return ret;
}

inline int Tests::parseArguments(int argc, char **argv) {
    constexpr auto helpText = R"(
--test [testname]       specify test
--do-not-catch -n       disable error handling in tests
--help                  print this text
)";
    // Let the user choose test from command line
    if (argc > 1) {
        auto args = std::vector<std::string>(argv + 1, argv + argc);

        if (args.at(0) == "-l") {
            std::cout << "available tests:" << std::endl;
            for (auto &test : tests) {
                std::cout << "Test Suit: " << test->testSuitName << "\n";

                if (!test->isEnabled) {
                    std::cout << "    "
                              << "disabled\n";
                    continue;
                }
                for (auto &entry : test->entries) {
                    std::cout << "    " << entry.name << "\n";
                }
            }
            return 0;
        }

        auto enabledTests = std::vector<std::string>{};
        auto enabledTestSuit = std::string{};

        for (size_t i = 0; i < args.size(); ++i) {
            auto arg = args.at(i);
            if (arg.front() == '-') {
                if (arg == "--test") {
                    auto name = args.at(++i);
                    enabledTests.push_back(std::move(name));
                }
                else if (arg == "--do-not-catch" || arg == "-n") {
                    shouldCatchExceptions = false;
                }
                else if (arg == "--help" || arg == "-h") {
                    std::cout << helpText << std::endl;
                    std::exit(0);
                }
                else {
                    std::cerr << "unvalid argument " << arg << "\n\n";
                    std::cerr << helpText << std::endl;
                    std::exit(1);
                }
            }
            else {
                enabledTestSuit = arg;
            }
        }

        if (!enabledTestSuit.empty()) {
            for (auto &test : tests) {
                test->isEnabled = test->testSuitName == enabledTestSuit;
            }
        }
    }

    return 1;
}

} // namespace unittest
