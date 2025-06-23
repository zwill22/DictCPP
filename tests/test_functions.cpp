#include "catch.hpp"

#include "dictcpp.hpp"

TEST_CASE("List of keys") {
    const auto dict1 = dictcpp::Dict<char, int>{
        {'a', 1},
        {'b', 2},
        {'c', 3}
    };

    const auto list1 = dictcpp::list(dict1);

    REQUIRE(list1.size() == 3);
    CHECK(list1[0] == 'a');
    CHECK(list1[1] == 'b');
    CHECK(list1[2] == 'c');

    const auto dict2 = dictcpp::Dict<char, int>{};
    const auto list2 = dictcpp::list(dict2);

    REQUIRE(list2.empty());
}

TEST_CASE("Length") {
    const auto dict1 = dictcpp::Dict<char, int>{
        {'a', 2},
        {'b', 4}
    };

    REQUIRE(dict1.size() == 2);
    CHECK(dictcpp::len(dict1) == dict1.size());

    const auto dict2 = dictcpp::Dict<char, int>{};
    REQUIRE(dict2.empty());
    CHECK(dictcpp::len(dict2) == dict2.size());
}

TEST_CASE("Free function constructor (single type)") {
    const auto dict1 = dictcpp::dict<int>({
        {1, 2},
        {2, 3},
        {4, 5}
    });

    REQUIRE(dict1.size() == 3);
    CHECK(dict1.at(1) == 2);
    CHECK(dict1.at(2) == 3);
    CHECK(dict1.at(4) == 5);
}

TEST_CASE("Free function constructor (different types)") {
    const auto dict1 = dictcpp::dict<int, char>({
        {1, 'f'},
        {2, 'k'},
        {3, 'j'}
    });

    REQUIRE(dict1.size() == 3);
    CHECK(dict1.at(1) == 'f');
    CHECK(dict1.at(2) == 'k');
    CHECK(dict1.at(3) == 'j');
}

TEST_CASE("From keys") {
    const std::vector keys = {1, 2, 3, 4, 5, 6};

    const auto dict1 = dictcpp::fromkeys<int, char>(keys);
    REQUIRE(dict1.size() == keys.size());
    CHECK(dict1.contains(1));
    CHECK(dict1.contains(2));
    CHECK(dict1.contains(3));
    CHECK(dict1.contains(4));
    CHECK(dict1.contains(5));
    CHECK(dict1.contains(6));

    const auto dict2 = dictcpp::fromkeys<int, char>(keys, '%');
    REQUIRE(dict2.size() == keys.size());
    CHECK(dict2.at(1) == '%');
    CHECK(dict2.at(2) == '%');
    CHECK(dict2.at(3) == '%');
    CHECK(dict2.at(4) == '%');
    CHECK(dict2.at(5) == '%');
    CHECK(dict2.at(6) == '%');
}