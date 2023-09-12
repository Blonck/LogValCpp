#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <utility>

TEST_CASE("negate", "[unary]") {
    auto val = GENERATE(-2.0, -1.0, 0.0, 1.0, 2.0);

    LogVal val1(val);

    val1.negate();
    REQUIRE(val1 == LogVal(-1.0 * val));
    REQUIRE(val1.to() == -1.0 * val);

    REQUIRE(LogVal(val).negate() == LogVal(-1.0 * val));
    REQUIRE(LogVal(val).negate().to() == -1.0 * val);

    LogVal val2 = val1.negate();
    REQUIRE(val2 == LogVal(val));
    REQUIRE(val2.to() == val);
}

TEST_CASE("operator+", "[unary]") {
    auto val = GENERATE(-2.0, -1.0, 0.0, 1.0, 2.0);

    LogVal val1(val);
    LogVal val1_copy = val1;

    REQUIRE(+val1 == LogVal(val));
    REQUIRE((+val1).to() == val);
    // val1 must not have changed
    REQUIRE(val1 == val1_copy);
    REQUIRE(val1.to() == val);

    LogVal val2 = +val1;
    REQUIRE(val2 == LogVal(val));
    REQUIRE(val2.to() == val);
}

TEST_CASE("operator-", "[unary]") {
    auto val = GENERATE(-2.0, -1.0, 0.0, 1.0, 2.0);

    LogVal val1(val);
    LogVal val1_copy = val1;

    REQUIRE(-val1 == LogVal(-val));
    REQUIRE((-val1).to() == -val);
    // val1 must not have changed
    REQUIRE(val1 == val1_copy);
    REQUIRE(val1.to() == val);

    LogVal val2 = -val1;
    REQUIRE(val2 == LogVal(-val));
    REQUIRE(val2.to() == -val);
}
