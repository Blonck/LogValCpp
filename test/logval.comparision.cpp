#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <utility>

TEST_CASE("Equal comparision", "[comparision]") {
    auto val = GENERATE(0.0, -0.0, 0.01, 2.0, 3456.0, 3.45e7, -2.0, -3.5e11);

    REQUIRE(LogVal(val) == LogVal(val));

    const LogVal val1(val);
    REQUIRE(val1 == LogVal(val));

    const LogVal val2(val);
    REQUIRE(val1 == val2);
}

TEST_CASE("Equal comparision - special cases", "[comparision]") {
    // The comparison requires that std::log(0) == std::log(0)
    REQUIRE(std::log(0) == std::log(0));

    auto rhs = GENERATE(-2.0, 0.0, 2.0);

    // After multiplication with 0, LogVals must be euqal
    // independently of the initialization.
    LogVal val1(1.0);
    LogVal val2(rhs);
    const LogVal null(0.0);
    val1 *= null;
    val2 *= null;

    REQUIRE(val1 == val2);

}

TEST_CASE("Unequal comparision", "[comparision]") {
    auto lhs = GENERATE(0.0, 0.01, 2.0, 3456.0, 3.45e7);
    auto rhs = GENERATE(0.003, -2.0, -42.0, -2.01e9);

    REQUIRE(LogVal(lhs) != LogVal(rhs));
    REQUIRE_FALSE(LogVal(lhs) != LogVal(lhs));
    REQUIRE_FALSE(LogVal(rhs) != LogVal(rhs));

    const LogVal val1(lhs);
    REQUIRE(val1 != LogVal(rhs));
    REQUIRE_FALSE(val1 != LogVal(val1));

    const LogVal val2(rhs);
    REQUIRE(val1 != val2);
    REQUIRE_FALSE(val1 != val1);
}

TEST_CASE("operator<=", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [lhs, rhs] = GENERATE(table<double, double>(
        {pair{-5.0, -2.0}, pair{-2.0, 0.0}, pair{-1.0, 1.0}, pair{0.0, 1.0},
         pair{1.0, 3.0}, pair{-1.0, -1.0}, pair{0.0, 0.0}, pair{1.0, 1.0}}));

    REQUIRE(LogVal(lhs) <= LogVal(rhs));
}

TEST_CASE("operator<= is false", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [rhs, lhs] = GENERATE(table<double, double>(
        {pair{-5.0, -2.0}, pair{-2.0, 0.0}, pair{-1.0, 1.0}, pair{0.0, 1.0},
         pair{1.0, 3.0}}));

    REQUIRE_FALSE(LogVal(lhs) <= LogVal(rhs));
}

TEST_CASE("operator<", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [lhs, rhs] = GENERATE(table<double, double>(
        {pair{-5.0, -2.0}, pair{-2.0, 0.0}, pair{-1.0, 1.0}, pair{0.0, 1.0},
         pair{1.0, 3.0}}));

    REQUIRE(LogVal(lhs) < LogVal(rhs));
}

TEST_CASE("operator< false", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [rhs, lhs] = GENERATE(table<double, double>(
        {pair{-5.0, -2.0}, pair{-2.0, 0.0}, pair{-1.0, 1.0}, pair{0.0, 1.0},
         pair{1.0, 3.0}, pair{-1.0, -1.0}, pair{0.0, 0.0}, pair{1.0, 1.0}}));

    REQUIRE_FALSE(LogVal(lhs) < LogVal(rhs));
}

TEST_CASE("operator>=", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [lhs, rhs] = GENERATE(table<double, double>(
        {pair{5.0, 2.0}, pair{2.0, 0.0}, pair{1.0, -1.0}, pair{-1.0, -3.0},
         pair{-1.0, -1.0}, pair{0.0, 0.0}, pair{1.0, 1.0}}));

    REQUIRE(LogVal(lhs) >= LogVal(rhs));
}

TEST_CASE("operator>", "[comparision]") {
    using pair = std::pair<double, double>;
    auto [lhs, rhs] = GENERATE(table<double, double>(
        {pair{5.0, 2.0}, pair{2.0, 0.0}, pair{1.0, -1.0}, pair{-1.0, -3.0}}));

    REQUIRE(LogVal(lhs) > LogVal(rhs));
}
