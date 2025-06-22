#include "dictcpp.hpp"
#include "catch.hpp"

using dictcpp::Dict;

TEST_CASE("Get values") {
    const auto dict = Dict<int, char>{
        {1, 'y'},
        {2, 'n'},
        {3, 'y'}
    };

    REQUIRE(dict.size() == 3);

    for (int key = 0; key < 10; key++) {
        if (key == 1 || key == 3) {
            CHECK(dict.get(key) == 'y');
        } else if (key == 2) {
            CHECK(dict.get(key) == 'n');
        } else {
            CHECK_THROWS_WITH(dict.get(key), "Key not found in dictionary and no default exists");
        }
    }

    for (int key = 0; key < 10; key++) {
        constexpr auto default_value = 'y';
        if (key != 2) {
            CHECK(dict.get(key, default_value) == 'y');
        } else {
            CHECK(dict.get(key, default_value) == 'n');
        }
    }

    for (int key = 0; key < 10; key++) {
        constexpr auto default_value = 'n';
        if (key == 1 || key == 3) {
            CHECK(dict.get(key, default_value) == 'y');
        } else {
            CHECK(dict.get(key, default_value) == 'n');
        }
    }
}

TEST_CASE("Pop values") {
    auto dict = Dict<char, int>{
        {'a', 1},
        {'b', 0},
        {'c', 1},
        {'d', 0}
    };

    REQUIRE(dict.size() == 4);
    CHECK_THROWS_WITH(dict.pop('e'), "Key not found in dictionary and no default exists");
    CHECK(dict.pop('e', 1) == 1);
    REQUIRE(dict.size() == 4);

    CHECK(dict.pop('d') == 0);
    REQUIRE(dict.size() == 3);
    CHECK(dict.at('a') == 1);
    CHECK(dict.at('b') == 0);
    CHECK(dict.at('c') == 1);

    CHECK_THROWS_WITH(dict.pop('d'), "Key not found in dictionary and no default exists");
    CHECK(dict.pop('d', 1) == 1);
    CHECK(dict.pop('d', 0) == 0);

    REQUIRE(dict.size() == 3);
    CHECK(dict.pop('b', 1) == 0);
    REQUIRE(dict.size() == 2);
    CHECK(dict.at('a') == 1);
    CHECK(dict.at('c') == 1);

    CHECK_THROWS_WITH(dict.pop('b'), "Key not found in dictionary and no default exists");
    CHECK(dict.pop('b', 1) == 1);
    CHECK(dict.pop('b', 0) == 0);

    REQUIRE(dict.size() == 2);
    CHECK(dict.pop('a', 0) == 1);
    CHECK(dict.size() == 1);
    CHECK(dict.at('c') == 1);

    CHECK_THROWS_WITH(dict.pop('a'), "Key not found in dictionary and no default exists");
    CHECK(dict.pop('a', 1) == 1);
    CHECK(dict.pop('a', 0) == 0);

    CHECK_THROWS_WITH(dict.pop('f'), "Key not found in dictionary and no default exists");
    CHECK(dict.pop('f', 1) == 1);
    CHECK(dict.pop('f', 0) == 0);
}

TEST_CASE("Popitem") {
    auto dict = Dict<int, char>{
        {1, 'a'},
        {-1, 'b'},
        {2, 'c'},
        {-2, 'd'}
    };

    REQUIRE(dict.size() == 4);

    const auto &[key4, value4] = dict.popitem();
    CHECK(key4 == -2);
    CHECK(value4 == 'd');

    REQUIRE(dict.size() == 3);

    const auto &[key3, value3] = dict.popitem();
    CHECK(key3 == 2);
    CHECK(value3 == 'c');

    REQUIRE(dict.size() == 2);

    const auto &[key2, value2] = dict.popitem();
    CHECK(key2 == -1);
    CHECK(value2 == 'b');

    REQUIRE(dict.size() == 1);

    const auto &[key1, value1] = dict.popitem();
    CHECK(key1 == 1);
    CHECK(value1 == 'a');

    REQUIRE(dict.size() == 0);

    CHECK_THROWS_WITH(dict.popitem(), "Dictionary is empty, no items to pop!");
}

TEST_CASE("Set default") {
    auto dict = Dict<char, int>{
        {'a', 11},
        {'b', 21},
        {'c', 41},
        {'d', 81}
    };

    REQUIRE(dict.size() == 4);
    CHECK(dict.setdefault('a')  == 11);
    CHECK(dict.setdefault('b') == 21);
    CHECK(dict.setdefault('c') == 41);
    CHECK(dict.setdefault('d') == 81);
    REQUIRE(dict.size() == 4);

    REQUIRE_FALSE(dict.contains('e'));
    dict.setdefault('e');
    REQUIRE(dict.size() == 5);
    REQUIRE(dict.contains('e'));
    dict['e'] = 0;
    CHECK(dict.setdefault('e', 161) == 0);
    REQUIRE(dict.size() == 5);
    CHECK(dict.setdefault('e', 321) == 0);

    REQUIRE_FALSE(dict.contains('f'));
    CHECK(dict.setdefault('f', 641) == 641);
    REQUIRE(dict.size() == 6);
    CHECK(dict.setdefault('f', 1273) == 641);
    CHECK(dict.setdefault('f') == 641);

    REQUIRE(dict.size() == 6);
    CHECK(dict.at('a') == 11);

}
