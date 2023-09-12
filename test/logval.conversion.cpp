#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <utility>

TEST_CASE("To type", "[conversion]") {
    // this works only for 1.0
    REQUIRE(LogVal(1.0).to<double>() == 1.0);
    REQUIRE(LogVal(-1.0).to<double>() == -1.0);

    REQUIRE(LogVal(0.0).to<double>() == 0.0);

    // this works only for 1.0
    REQUIRE(LogVal<float>(1.0F).to<float>() == 1.0F);
    REQUIRE(LogVal<float>(-1.0F).to<float>() == -1.0F);
}
