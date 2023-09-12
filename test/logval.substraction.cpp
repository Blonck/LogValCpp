#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <utility>

TEST_CASE("Assignment substraction", "[minus]") {
    constexpr double eps = 1e-9;
    auto lhs = GENERATE(-2.0, -1.0, 0.0, 1.0, 2.0);
    auto rhs = GENERATE(-3.0, -1.0, 0.0, 1.0, 3.0);

    LogVal tmp = LogVal(lhs);
    tmp -= LogVal(rhs);
    REQUIRE_THAT(tmp.to(), Catch::Matchers::WithinAbs(lhs - rhs, eps));
}

TEST_CASE("Assignment substraction with larger numbers", "[minus]") {
    auto lhs = GENERATE(1.0, -20000.0, 3.46e9, -2.34e7);
    auto rhs = GENERATE(-1.0, 23112.3, -4.46e9, 2.34e7);

    LogVal tmp = LogVal(lhs);
    tmp -= LogVal(rhs);
    REQUIRE_THAT(tmp.to(), Catch::Matchers::WithinRel(lhs - rhs));
}

TEST_CASE("Substraction", "[minus]") {
    constexpr double eps = 1e-9;
    auto lhs = GENERATE(-2.0, -1.0, 0.0, 1.0, 2.0);
    auto rhs = GENERATE(-3.0, -1.0, 0.0, 1.0, 3.0);

    REQUIRE_THAT((LogVal(lhs) + LogVal(rhs)).to(),
                 Catch::Matchers::WithinAbs(lhs + rhs, eps));

    const LogVal val1(lhs);
    const LogVal val2(rhs);
    REQUIRE_THAT((val1 - val2).to(),
                 Catch::Matchers::WithinAbs(lhs - rhs, eps));
}

TEST_CASE("Substraction with large numbers", "[minus]") {
    auto lhs = GENERATE(1.0, -20000.0, 3.46e9, -2.34e7);
    auto rhs = GENERATE(-1.0, 23112.3, -4.46e9, 2.34e7);

    REQUIRE_THAT((LogVal(lhs) + LogVal(rhs)).to(),
                 Catch::Matchers::WithinRel(lhs + rhs));

    const LogVal val1(lhs);
    const LogVal val2(rhs);
    REQUIRE_THAT((val1 - val2).to(), Catch::Matchers::WithinRel(lhs - rhs));
}
