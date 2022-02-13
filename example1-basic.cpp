#include "unittest.h"
#include <limits>
#include <memory>

TEST_SUIT_BEGIN

TEST_CASE("Bool assertions") {
    struct S {};

    bool x = true;
    bool y = false;

    EXPECT_TRUE(x);
    EXPECT_FALSE(y);

    auto s = std::make_unique<S>();

    // Works for pointers aswell
    EXPECT_TRUE(s);
}

TEST_CASE("float and numeric assertions") {
    auto x = 10.;
    auto y = 20.;
    auto z = x;

    EXPECT_GT(y, x);
    EXPECT_LT(x, y);
    EXPECT_NEAR(x, z, std::numeric_limits<double>::min());
}

TEST_CASE("exceptions") {
    auto f = []() { throw std::runtime_error{"error"}; };

    EXPECT_THROW(f(), std::runtime_error);
}

TEST_CASE("disabled unused test") {
    // This will never run
}

TEST_SUIT_END
