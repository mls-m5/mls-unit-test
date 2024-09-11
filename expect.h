#pragma once

#include "unittestvars.h"

#define PRINT_INFO std::cout << __FILE__ << ":" << __LINE__ << ": ";
#define ASSERT(test_var_x, error)                                              \
    if (!(test_var_x)) {                                                       \
        PRINT_INFO;                                                            \
        unittest::failTest();                                                  \
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
        unittest::failTest();                                                  \
        std::cout << #test_var_x << " = '" << test_var_x                       \
                  << "' is not equal to " << #test_var_y << " = '"             \
                  << test_var_y << "'" << std::endl;                           \
        unittest::failTest();                                                  \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_NE(test_var_x, test_var_y)                                      \
    if ((test_var_x) == (test_var_y)) {                                        \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x << " is equal to "     \
                  << #test_var_y << " = " << test_var_y << std::endl;          \
        unittest::failTest();                                                  \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_GT(test_var_x, test_var_y)                                      \
    if (!((test_var_x) > (test_var_y))) {                                      \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x                        \
                  << " is not greater than " << #test_var_y << " = "           \
                  << test_var_y << std::endl;                                  \
        unittest::failTest();                                                  \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_LT(test_var_x, test_var_y)                                      \
    if (!((test_var_x) < (test_var_y))) {                                      \
        PRINT_INFO;                                                            \
        std::cout << #test_var_x << " = " << test_var_x                        \
                  << " is not less than " << #test_var_y << " = "              \
                  << test_var_y << std::endl;                                  \
        unittest::failTest();                                                  \
        return;                                                                \
    }                                                                          \
    unittest::semicolon()

#define EXPECT_NEAR(test_var_x, test_var_y, test_var_e)                        \
    {                                                                          \
        auto a = (test_var_x);                                                 \
        auto b = (test_var_y);                                                 \
        if (!(a + test_var_e > b) || !(a < b + test_var_e)) {                  \
            PRINT_INFO;                                                        \
            std::cout << #test_var_x << " == " << test_var_x                   \
                      << " is not near " << #test_var_y << std::endl;          \
            unittest::failTest();                                              \
            return;                                                            \
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
            unittest::failTest();                                              \
            return;                                                            \
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
            unittest::failTest();                                              \
            return;                                                            \
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
            unittest::failTest();                                              \
            return;                                                            \
        }                                                                      \
    }                                                                          \
    unittest::semicolon()

#define ERROR(error)                                                           \
    PRINT_INFO;                                                                \
    std::cout << error << std::endl;                                           \
    unittest::failTest();                                                      \
    return;                                                                    \
    unittest::semicolon()

// The not implemented error is used to flag for wanted features not implemented
#define ERROR_NOT_IMPLEMENTED()                                                \
    PRINT_INFO;                                                                \
    std::cout << "not implemented" << std::endl;                               \
    *testResult = -1;                                                          \
    return;                                                                    \
    unittest::semicolon()
