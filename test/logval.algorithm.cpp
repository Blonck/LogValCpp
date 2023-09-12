#include <LogValCpp/LogVal.hpp>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <functional>
#include <numeric>
#include <vector>

#include "catch2/matchers/catch_matchers.hpp"

TEST_CASE("accumulate", "[algorithm]") {
    std::vector<LogVal<double>> vec(10, LogVal(1.0));

    // vector is size 10 and filled with LogVal(1.0)
    REQUIRE(vec.size() == 10);
    for (const auto &e : vec) {
        REQUIRE(e == LogVal(1.0));
    }

    SECTION("Multiplication via lambda") {
        auto res =
            std::accumulate(vec.cbegin(), vec.cend(), LogVal(1.0),
                            [](auto acc, auto val) { return acc * val; });
        REQUIRE(res == LogVal(1.0));
    }

    SECTION("Multiplication via std::multiplies") {
        auto res = std::accumulate(vec.cbegin(), vec.cend(), LogVal(1.0),
                                   std::multiplies<>());
        REQUIRE(res == LogVal(1.0));
    }

    SECTION("Addition via lambda") {
        auto res =
            std::accumulate(vec.cbegin(), vec.cend(), LogVal(0.0),
                            [](auto acc, auto val) { return acc + val; });
        REQUIRE_THAT(res.to(), Catch::Matchers::WithinRel(
                                   static_cast<double>(vec.size())));
    }

    SECTION("Multiplication with large numbers") {
        constexpr double eps = 1e-7;

        std::vector<LogVal<double>> large_vec(10000, LogVal(1e30));
        auto res = std::accumulate(large_vec.cbegin(), large_vec.cend(),
                                   LogVal(1.0), std::multiplies<>());
        auto res2 = std::accumulate(large_vec.cbegin(), large_vec.cend(), res,
                                    std::divides<>());

        REQUIRE_THAT(res2.to(), Catch::Matchers::WithinAbs(1.0, eps));
    }
}
