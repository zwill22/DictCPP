#include "dictcpp.hpp"
#include "tests/catch.hpp"

using dictcpp::Item;
using dictcpp::Dict;

TEST_CASE("Empty dict") {
    const auto dict = Dict<char, int>();
    REQUIRE(dict.empty());
}

TEST_CASE("Element assignment") {
    auto dict = Dict<int>();
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
    auto dict = Dict<int>();
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
        auto dict1 = Dict<char, int>();
        dict1['2'] = 20;
        dict1['3'] = 100;
        return dict1;
    }();

    REQUIRE(dict.size() == 2);
    CHECK(dict['2'] == 20);
    CHECK(dict.at('2') == 20);

    CHECK(dict['3'] == 100);
    CHECK(dict.at('3') == 100);

    const auto value = dict['2'];
    CHECK(value == 20);
    const auto value2 = dict['3'];
    CHECK(value2 == 100);

    auto value3 = dict['2'];
    CHECK(value3 == 20);
    value3 = 100;
    CHECK(value3 == 100);
    CHECK(dict['2'] == 20);
    CHECK(dict.at('2') == 20);

    auto value4 = dict['3'];
    CHECK(value4 == 100);
    value4 = 200;
    CHECK(value4 == 200);
    CHECK(dict['3'] == 100);
    CHECK(dict.at('3') == 100);

    CHECK_THROWS_WITH(dict.at('5'), "Key not found in dictionary");
    CHECK_THROWS_WITH(dict['6'], "Key not found in dictionary");
}

TEST_CASE("Sequence initializer") {
    std::vector<Item<char>> values = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};

    const auto dict = Dict(values);

    REQUIRE(dict.size() == values.size());

    CHECK(dict['a'] == 'b');
    CHECK(dict['c'] == 'd');
    CHECK(dict['e'] == 'f');

    values.emplace_back('a', 'g');
    REQUIRE(values.back().key == 'a');
    REQUIRE(values.back().value == 'g');

    const auto dict2 = Dict(values);
    REQUIRE(dict2.size() == dict.size());

    CHECK(dict2['a'] == 'g');
    CHECK(dict2['c'] == 'd');
    CHECK(dict2['e'] == 'f');
}

TEST_CASE("Access iterators") {
    const auto dict = Dict<int>({
        Item{1, 2},
        Item{3, 4},
        Item{5, 6},
        Item{7, 8},
        Item{9, 10}
    });

    const auto keys = dict.keys();

    REQUIRE(keys.size() == 5);
    CHECK(keys[0] == 1);
    CHECK(keys[1] == 3);
    CHECK(keys[2] == 5);
    CHECK(keys[3] == 7);
    CHECK(keys[4] == 9);

    const auto values = dict.values();
    REQUIRE(values.size() == 5);
    CHECK(values[0] == 2);
    CHECK(values[1] == 4);
    CHECK(values[2] == 6);
    CHECK(values[3] == 8);
    CHECK(values[4] == 10);

    const auto items = dict.items();
    REQUIRE(items.size() == 5);
    size_t i = 0;
    for (const auto &[key, value]: items) {
        CHECK(key == keys[i]);
        CHECK(value == values[i]);
        i++;
    }
}
