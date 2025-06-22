#include "dictcpp.hpp"

#include "catch.hpp"

using dictcpp::Dict;
using dictcpp::Item;

TEST_CASE("Loop through dictionary") {
    const auto dictionary = Dict(
        std::vector{
            Item{'a', 2},
            Item{'b', 3},
            Item{'c', 4},
            Item{'d', 5}
        }
    );

    size_t i = 0;
    const auto keys = dictionary.keys();
    REQUIRE(keys.size() == dictionary.size());

    for (const auto &key: dictionary) {
        CHECK(key == keys[i++]);
    }
}

TEST_CASE("Loop through non-const dictionary") {
    auto dictionary = Dict<size_t, double>();
    const std::vector<size_t> keys = {1, 2, 3};
    const std::vector<double> values = {20, 40, 80};
    REQUIRE(values.size() == keys.size());

    for (size_t i = 0; i < keys.size(); ++i) {
        const auto key = keys[i];
        const auto value = values[i];

        dictionary[key] = value;
    }

    dictionary[1] = 20;
    dictionary[2] = 30;
    dictionary[3] = 50;

    for (auto key: dictionary) {
        const auto original_value = key;
        key = key * 2;
        REQUIRE(key == 2 * original_value);
    }

    REQUIRE(dictionary.size() == keys.size());
    const auto dictionary_keys = dictionary.keys();
    for (size_t i = 0; i < keys.size(); ++i) {
        CHECK(dictionary_keys[i] == keys[i]);
    }

    for (auto &key: dictionary) {
        key = key + 3;
    }

    const auto new_keys = dictionary.keys();
    REQUIRE(new_keys.size() == dictionary.size());
    for (size_t i = 0; i < new_keys.size(); ++i) {
        CHECK(new_keys[i] == keys[i] + 3);
    }
}
