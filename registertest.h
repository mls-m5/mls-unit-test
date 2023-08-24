#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <string_view>

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

    void run();

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
    };

    /// List instead of vector to keep position in memory
    std::list<TestEntry> entries;

    std::string testSuitName;
    int testResult = 0;

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

    int run() {
        using std::cout;
        using std::endl;
        int numFailed = 0;
        int numSucceded = 0;
        int numInactive = 0;

        //        if (!parseArguments(argc, argv)) {
        //            return 0;
        //        }

        //        if (setup) {
        //            setup();
        //        }

        cout << "==== Starts test suit " << testSuitName << " ====" << endl
             << endl;

        for (auto &it : entries) {
            if (it.name.rfind("disabled ", 0) == 0) {
                it.result = "disabled";
                //                it.result = "disabled";
                ++numInactive;
                continue;
            }

            cout << "=== running test: " << it.name << " ===" << endl;
            testResult = 0;

#ifdef DO_NOT_CATCH_ERRORS
            it.f();
#else
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
#endif
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

// struct RegisterTestStatic {
//     Tests::TestEntry &entry;

//    RegisterTestStatic(const RegisterTestStatic &) = default;
//    RegisterTestStatic(RegisterTestStatic &&) = default;
//    RegisterTestStatic &operator=(const RegisterTestStatic &) = delete;
//    RegisterTestStatic &operator=(RegisterTestStatic &&) = delete;
//    ~RegisterTestStatic();

//    RegisterTestStatic(std::string_view suitName, std::string_view testName)
//        : entry{Tests::instance().add(suitName, testName)} {}

//    RegisterTestStatic &operator=(std::function<void()> f) {
//        entry.f = f;
//        return *this;
//    }
//};

inline Tests::~Tests() = default;

inline void Tests::run() {
    for (auto &test : tests) {
        test->run();
    }
}

} // namespace unittest
