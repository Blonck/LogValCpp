#include <LogValCpp/LogVal.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <utility>

TEST_CASE("Compiles & runs", "[base]") {
    REQUIRE(1 == 1 * 1);
    REQUIRE(1 + 1 == 2);
}
