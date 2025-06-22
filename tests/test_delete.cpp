#include "dictcpp.hpp"

#include "catch.hpp"

using dictcpp::Dict;
using dictcpp::Item;

TEST_CASE("Deletions") {
    auto dict = Dict<char, int>{
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4}
    };

    CHECK_THROWS_WITH(dict.del('e'), "Key not found in dictionary");
    REQUIRE(dict.size() == 4);

    const auto keys4 = dict.keys();
    REQUIRE(keys4.size() == 4);
    CHECK(keys4[0] == 'a');
    CHECK(keys4[1] == 'b');
    CHECK(keys4[2] == 'c');
    CHECK(keys4[3] == 'd');

    const auto values4 = dict.values();
    REQUIRE(values4.size() == 4);
    CHECK(values4[0] == 1);
    CHECK(values4[1] == 2);
    CHECK(values4[2] == 3);
    CHECK(values4[3] == 4);

    dict.del('b');
    REQUIRE(dict.size() == 3);
    CHECK(dict.contains('a'));
    CHECK_FALSE(dict.contains('b'));
    CHECK(dict.contains('c'));
    CHECK(dict.contains('d'));

    const auto keys3 = dict.keys();
    REQUIRE(keys3.size() == 3);
    CHECK(keys3[0] == 'a');
    CHECK(keys3[1] == 'c');
    CHECK(keys3[2] == 'd');

    const auto values3 = dict.values();
    REQUIRE(values3.size() == 3);
    CHECK(values3[0] == 1);
    CHECK(values3[1] == 3);
    CHECK(values3[2] == 4);

    CHECK_THROWS_WITH(dict.del('b'), "Key not found in dictionary");
    REQUIRE(dict.size() == 3);

    dict.del('c');
    REQUIRE(dict.size() == 2);
    CHECK(dict.contains('a'));
    CHECK_FALSE(dict.contains('b'));
    CHECK_FALSE(dict.contains('c'));
    CHECK(dict.contains('d'));

    const auto keys2 = dict.keys();
    REQUIRE(keys2.size() == 2);
    CHECK(keys2[0] == 'a');
    CHECK(keys2[1] == 'd');

    const auto values2 = dict.values();
    REQUIRE(values2.size() == 2);
    CHECK(values2[0] == 1);
    CHECK(values2[1] == 4);

    CHECK_THROWS_WITH(dict.del('c'), "Key not found in dictionary");
    REQUIRE(dict.size() == 2);

    dict.del('a');
    REQUIRE(dict.size() == 1);
    CHECK_FALSE(dict.contains('a'));
    CHECK_FALSE(dict.contains('b'));
    CHECK_FALSE(dict.contains('c'));
    CHECK(dict.contains('d'));

    const auto keys1 = dict.keys();
    REQUIRE(keys1.size() == 1);
    CHECK(keys1[0] == 'd');

    const auto values1 = dict.values();
    REQUIRE(values1.size() == 1);
    CHECK(values1[0] == 4);

    CHECK_THROWS_WITH(dict.del('a'), "Key not found in dictionary");
    REQUIRE(dict.size() == 1);

    dict.del('d');
    REQUIRE(dict.empty());
}

TEST_CASE("Clear") {
    auto dict = Dict<char, int>{
        {'a', 1},
        {'c', 2},
        {'e', 4},
        {'g', 8}
    };

    REQUIRE(dict.size() == 4);

    dict.clear();
    REQUIRE(dict.empty());

    CHECK(dict.keys().empty());
    CHECK(dict.values().empty());
    CHECK(dict.items().empty());
}
