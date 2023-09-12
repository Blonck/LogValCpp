
#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>
#include <iostream>
#include <utility>

#include "catch2/matchers/catch_matchers.hpp"

TEST_CASE("Assignment division with 1.0", "[division]") {
    SECTION("1.0 /= 1.0") {
        LogVal val1(1.0);
        val1 /= LogVal(1.0);
        REQUIRE(val1 == LogVal(1.0));

        // val1 /= val1;
        // REQUIRE(val1 == LogVal(1.0));

        const LogVal val2(1.0);
        val1 /= val2;
        REQUIRE(val1 == LogVal(1.0));
    }

    SECTION("1.0 /= -1.0") {
        LogVal val1(1.0);
        val1 /= LogVal(-1.0);
        REQUIRE(val1 == LogVal(-1.0));

        const LogVal val2(-1.0);
        val1 = LogVal(1.0);
        val1 /= val2;
        REQUIRE(val1 == LogVal(-1.0));
    }
}

TEST_CASE("Assignment division", "[division]") {
    auto lhs = GENERATE(0.01, 2.0, -2.0, 3456.0, 3.45e7);
    auto rhs = GENERATE(0.003, 2.0, -2.0, -42.0, -2.01e9);

    LogVal val1(lhs);
    val1 /= LogVal(rhs);
    REQUIRE_THAT(val1.to(), Catch::Matchers::WithinRel(lhs / rhs));
}

TEST_CASE("Division with 1.0", "[division]") {
    SECTION("1.0 / 1.0") {
        REQUIRE(LogVal(1.0) / LogVal(1.0) == LogVal(1.0));

        const LogVal val1(1.0);
        REQUIRE(val1 / LogVal(1.0) == LogVal(1.0));

        const LogVal val2(1.0);
        REQUIRE(val1 / val2 == LogVal(1.0));
    }

    SECTION("1.0/-1.0") {
        REQUIRE(LogVal(1.0) / LogVal(-1.0) == LogVal(-1.0));

        const LogVal val1(1.0);
        REQUIRE(val1 / LogVal(-1.0) == LogVal(-1.0));

        const LogVal val2(-1.0);
        REQUIRE(val2 / LogVal(1.0) == LogVal(-1.0));

        const LogVal val3(-1.0);
        REQUIRE(val1 / val3 == LogVal(-1.0));
    }

    SECTION("-1.0/-1.0") {
        REQUIRE(LogVal(-1.0) / LogVal(-1.0) == LogVal(1.0));

        const LogVal val1(-1.0);
        REQUIRE(val1 / LogVal(-1.0) == LogVal(1.0));

        const LogVal val2(-1.0);
        REQUIRE(val1 / val2 == LogVal(1.0));
    }
}

TEST_CASE("Division", "[division]") {
    auto lhs = GENERATE(0.0, 0.01, 2.0, -2.0, 3456.0, 3.45e7);
    auto rhs = GENERATE(0.003, 2.0, -2.0, -42.0, -2.01e9);

    REQUIRE_THAT((LogVal(lhs) / LogVal(rhs)).to(),
                 Catch::Matchers::WithinRel(lhs / rhs));

    const LogVal val1(lhs);
    const LogVal val2(rhs);

    REQUIRE_THAT((val1 / val2).to(), Catch::Matchers::WithinRel(lhs / rhs));
}

TEST_CASE("Division with 0.0", "[division]") {
    auto lhs = GENERATE(-1.0, 0.0, 1.0);

    // not decided for now how LogVal should behave
    REQUIRE_FALSE(std::isfinite((LogVal(lhs) / LogVal(0.0)).to()));
}
