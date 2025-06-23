#include "catch.hpp"

#include "dictcpp.hpp"

using dictcpp::Dict;

TEST_CASE("Update dictionary") {
    auto dict1 = Dict<int, char>{
        {1, 'a'},
        {2, 'b'},
        {4, 'c'},
        {8, 'e'}
    };

    const auto dict2 = Dict<int, char>{
        {2, 'z'},
        {8, 'g'},
        {16, 'j'},
        {32, 'm'},
        {64, 't'}
    };

    REQUIRE(dict1.size() == 4);
    REQUIRE(dict2.size() == 5);

    dict1.update(dict2);

    REQUIRE(dict1.size() == 7);
    REQUIRE(dict2.size() == 5);

    CHECK(dict1.at(1) == 'a');
    CHECK(dict1.at(2) == 'z');
    CHECK(dict1.at(4) == 'c');
    CHECK(dict1.at(8) == 'g');
    CHECK(dict1.at(16) == 'j');
    CHECK(dict1.at(32) == 'm');
    CHECK(dict1.at(64) == 't');
}


TEST_CASE("Merge dictionaries") {
    const auto dict1 = Dict<int, char>{
            {1, 'a'},
            {2, 'b'},
            {4, 'c'},
            {8, 'e'}
    };

    const auto dict2 = Dict<int, char>{
            {2, 'z'},
            {8, 'g'},
            {16, 'j'},
            {32, 'm'},
            {64, 't'}
    };

    REQUIRE(dict1.size() == 4);
    REQUIRE(dict2.size() == 5);

    const auto dict3 = dict1 | dict2;

    REQUIRE(dict3.size() == 7);

    CHECK(dict3.at(1) == 'a');
    CHECK(dict3.at(2) == 'z');
    CHECK(dict3.at(4) == 'c');
    CHECK(dict3.at(8) == 'g');
    CHECK(dict3.at(16) == 'j');
    CHECK(dict3.at(32) == 'm');
    CHECK(dict3.at(64) == 't');
}

TEST_CASE("Update dictionary with |=") {
    auto dict1 = Dict<int, char>{
            {1, 'a'},
            {2, 'b'},
            {4, 'c'},
            {8, 'd'}
    };

    const auto dict2 = Dict<int, char>{
            {2, 'e'},
            {8, 'f'},
            {16, 'g'},
            {32, 'h'},
            {64, 'i'}
    };

    REQUIRE(dict1.size() == 4);
    REQUIRE(dict2.size() == 5);

    dict1 |= dict2;

    REQUIRE(dict1.size() == 7);
    REQUIRE(dict2.size() == 5);

    CHECK(dict1.at(1) == 'a');
    CHECK(dict1.at(2) == 'e');
    CHECK(dict1.at(4) == 'c');
    CHECK(dict1.at(8) == 'f');
    CHECK(dict1.at(16) == 'g');
    CHECK(dict1.at(32) == 'h');
    CHECK(dict1.at(64) == 'i');
}

TEST_CASE("Update dictionary with |= initializer list") {
    auto dict1 = Dict<int, char>{
                {1, 'a'},
                {2, 'b'},
                {4, 'c'},
                {8, 'd'}
    };

    dict1 |= {
                {2, 'e'},
                {8, 'f'},
                {16, 'g'},
                {32, 'h'},
                {64, 'i'}
    };

    REQUIRE(dict1.size() == 7);

    CHECK(dict1.at(1) == 'a');
    CHECK(dict1.at(2) == 'e');
    CHECK(dict1.at(4) == 'c');
    CHECK(dict1.at(8) == 'f');
    CHECK(dict1.at(16) == 'g');
    CHECK(dict1.at(32) == 'h');
    CHECK(dict1.at(64) == 'i');
}

TEST_CASE("Update dictionary with |= vector") {
    auto dict1 = Dict<int, char>{
                    {1, 'a'},
                    {2, 'b'},
                    {4, 'c'},
                    {8, 'd'}
    };

    const auto extra = std::vector<dictcpp::Item<int, char>>{
                    {2, 'e'},
                    {8, 'f'},
                    {16, 'g'},
                    {32, 'h'},
                    {64, 'i'}
    };

    dict1 |= extra;

    REQUIRE(dict1.size() == 7);

    CHECK(dict1.at(1) == 'a');
    CHECK(dict1.at(2) == 'e');
    CHECK(dict1.at(4) == 'c');
    CHECK(dict1.at(8) == 'f');
    CHECK(dict1.at(16) == 'g');
    CHECK(dict1.at(32) == 'h');
    CHECK(dict1.at(64) == 'i');
}
