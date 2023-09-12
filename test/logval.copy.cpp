#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <iostream>
#include <utility>

TEST_CASE("Copy constructor", "[copy]") {
    auto val = GENERATE(-1.0, 0.0, 1.0);

    const LogVal val1(val);
    LogVal val2(val1);

    REQUIRE(val1.to() == val);
    REQUIRE(val1.to() == val2.to());

    // val1 should not reference val2 in any way
    val2 = LogVal(3.0);
    REQUIRE(val1.to() == val);
}

TEST_CASE("Copy assignment operator", "[copy]") {
    auto val = GENERATE(-1.0, 0.0, 1.0);

    const LogVal val1 = LogVal(val);
    REQUIRE(val1.to() == val);

    LogVal val2 = val1;
    REQUIRE(val2.to() == val);

    // val1 should not reference val2 in any way
    val2 = LogVal(3.0);
    REQUIRE(val1.to() == val);
}
