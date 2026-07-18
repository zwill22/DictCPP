#include "catch.hpp"

#include "dictcpp.hpp"

TEST_CASE(
        "Map initialisation"
) {
    const auto map = std::map<int, char> {{1, 2}, {3, 4}};

    const auto dict = dictcpp::Dict(map);
    REQUIRE(map.size() == dict.size());

    for (const auto &key: dict) {
        REQUIRE(map.contains(key));

        CHECK(map.at(key) == dict.at(key));
    }
}

TEST_CASE(
        "Dict to map"
) {
    const auto dict = dictcpp::Dict<char, int> {{'a', 2}, {'b', 4}, {'c', 6}};

    const auto map = dict.map();

    REQUIRE(map.size() == dict.size());
    for (const auto &key: dict) {
        REQUIRE(map.contains(key));
        CHECK(map.at(key) == dict.at(key));
    }
}

TEST_CASE(
        "Update dictionary"
) {
    auto dict = dictcpp::Dict<char, int> {{'a', 3}, {'c', 4}, {'b', 3}};

    const auto map = std::map<char, int> {{'c', 5}, {'b', 2}, {'d', 1}};

    dict.update(map);

    REQUIRE(dict.size() == 4);
    CHECK(dict.at('a') == 3);
    CHECK(dict.at('b') == 2);
    CHECK(dict.at('c') == 5);
    CHECK(dict.at('d') == 1);
}

TEST_CASE(
        "Update dictionary operator"
) {
    auto dict = dictcpp::Dict<char, int> {{'a', 3}, {'c', 4}, {'b', 3}};

    const auto map = std::map<char, int> {{'c', 5}, {'b', 2}, {'d', 1}};

    dict |= map;

    REQUIRE(dict.size() == 4);
    CHECK(dict.at('a') == 3);
    CHECK(dict.at('b') == 2);
    CHECK(dict.at('c') == 5);
    CHECK(dict.at('d') == 1);
}
