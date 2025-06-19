#include "dictcpp.hpp"
#include "tests/catch.hpp"

TEST_CASE("Empty dict") {
    const auto dict = dictcpp::Dict<char, char>();
    REQUIRE(dict.empty());
}

TEST_CASE("Element assignment") {
    auto dict = dictcpp::Dict<int, int>();
    REQUIRE(dict.empty());

    dict[2] = 20;
    REQUIRE(dict.size() == 1);
    CHECK(dict[2] == 20);
    CHECK(dict.at(2) == 20);

    dict[2] = 100;
    REQUIRE(dict.size() == 1);
    CHECK(dict[2] == 100);
    CHECK(dict.at(2) == 100);

    dict[2];
    CHECK(dict.size() == 1);
    CHECK(dict[2] == 100);
    CHECK(dict.at(2) == 100);

    dict[3];
    REQUIRE(dict.size() == 2);

    dict[3] = 200;
    REQUIRE(dict.size() == 2);
    CHECK(dict[3] == 200);
    CHECK(dict.at(3) == 200);
}

TEST_CASE("Element at assignment") {
    auto dict = dictcpp::Dict<int, int>();
    REQUIRE(dict.empty());

    dict.at(2) = 20;
    REQUIRE(dict.size() == 1);
    CHECK(dict[2] == 20);
    CHECK(dict.at(2) == 20);

    dict.at(2) = 100;
    REQUIRE(dict.size() == 1);
    CHECK(dict[2] == 100);
    CHECK(dict.at(2) == 100);

    dict.at(2);
    CHECK(dict.size() == 1);
    CHECK(dict[2] == 100);
    CHECK(dict.at(2) == 100);

    dict.at(3);
    REQUIRE(dict.size() == 2);

    dict.at(3) = 200;
    REQUIRE(dict.size() == 2);
    CHECK(dict[3] == 200);
    CHECK(dict.at(3) == 200);
}

TEST_CASE("Element access") {
    const auto dict = [] {
        auto dict1 = dictcpp::Dict<int, int>();
        dict1[2] = 20;
        dict1[3] = 100;
        return dict1;
    }();

    REQUIRE(dict.size() == 2);
    CHECK(dict[2] == 20);
    CHECK(dict.at(2) == 20);

    CHECK(dict[3] == 100);
    CHECK(dict.at(3) == 100);

    const auto value = dict[2];
    CHECK(value == 20);
    const auto value2 = dict[3];
    CHECK(value2 == 100);

    auto value3 = dict[2];
    CHECK(value3 == 20);
    value3 = 100;
    CHECK(value3 == 100);
    CHECK(dict[2] == 20);
    CHECK(dict.at(2) == 20);

    auto value4 = dict[3];
    CHECK(value4 == 100);
    value4 = 200;
    CHECK(value4 == 200);
    CHECK(dict[3] == 100);
    CHECK(dict.at(3) == 100);

    CHECK_THROWS_WITH(dict.at(5), "Key not found in dictionary");
    CHECK_THROWS_WITH(dict[6], "Key not found in dictionary");
}
