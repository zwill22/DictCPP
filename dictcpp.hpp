#ifndef DICTCPP_HPP
#define DICTCPP_HPP
#include <set>
#include <vector>

namespace dictcpp {
/// A structure representing a single item (key-value pair) in a dictionary.
/// Key
///
/// @tparam Key Type of item `key`
/// @tparam Value Type of item `value` (default: `Key`)
template<typename Key, typename Value = Key>
struct Item {
    Key key;
    Value value;
};

/// A C++ implementation of a Python-like dictionary
///
/// @tparam Key Type of dictionary `keys`
/// @tparam Value Type of dictionary `values` (default: `Key`)
template<typename Key, typename Value = Key>
class Dict {
    std::vector<Key> key_list;
    std::vector<Value> val_list;

    bool key_exists(const Key &key) const {
        return std::set<Key>(key_list.begin(), key_list.end()).contains(key);
    }

    size_t get_index(const Key &key) const {
        for (size_t i = 0; i < key_list.size(); i++) {
            if (key_list[i] == key) {
                return i;
            }
        }
        throw std::logic_error("`get_index` called but key not in dictionary");
    }

public:
    /// Initialise an empty dictionary
    Dict(): key_list({}), val_list({}) {
    }

    /// Initialise a dictionary using a list of `Item`s.
    ///
    /// @param key_values A list of dictionary `Item`s (key-value pair)
    Dict(const std::initializer_list<Item<Key, Value>> &key_values) : key_list(), val_list() {
        for (const auto &kv: key_values) {
            if (key_exists(kv.key)) {
                const auto index = get_index(kv.key);
                val_list[index] = kv.value;
            } else {
                key_list.emplace_back(kv.key);
                val_list.emplace_back(kv.value);
            }
        }
    }

    /// Initialise a dictionary using a std::vector
    ///
    /// @param key_values Key-value pairs in a vector
    explicit Dict(const std::vector<Item<Key, Value>> &key_values) {
        for (const auto &kv: key_values) {
            if (key_exists(kv.key)) {
                const auto index = get_index(kv.key);
                val_list[index] = kv.value;
            } else {
                key_list.emplace_back(kv.key);
                val_list.emplace_back(kv.value);
            }
        }
    }

    /// Check if a dictionary is empty
    ///
    /// @return Whether the dictionary is empty or not
    [[nodiscard]] bool empty() const {
        return key_list.empty();
    }

    /// Get the current size of the dictionary
    ///
    /// @return Get the current size of the dictionary (number of keys)
    [[nodiscard]] size_t size() const {
        return key_list.size();
    }

    /// Access value at key `key`
    ///
    /// @param key Dictionary key
    ///
    /// @throws std::out_of_range If key not in dictionary
    ///
    /// @return Constant reference to value at `dict[key]`
    const Value &operator[](const Key &key) const {
        if (!key_exists(key)) {
            throw std::out_of_range("Key not found in dictionary");
        }

        return val_list[get_index(key)];
    }

    /// Access value at `key` (wrapper to `operator[] const`)
    ///
    /// @param key Dictionary key
    ///
    /// @return Constant reference to value at `dict[key]`
    const Value &at(const Key &key) const {
        return operator[](key);
    }

    /// Access the value at key `key` or assign value to key `key`
    ///
    /// @param key Dictionary key
    ///
    /// @return Reference to value at `dict[key]`
    Value &operator[](const Key &key) {
        if (key_exists(key)) {
            const auto index = get_index(key);

            return val_list[index];
        }

        key_list.push_back(key);
        val_list.push_back({});

        return *(std::end(val_list) - 1);
    }

    /// Access value at `key` or assign value at `key` (wrapper for `operator[]`)
    ///
    /// @param key Dictionary key
    ///
    /// @return Reference to value at `dict[key]`
    Value &at(const Key &key) {
        return operator[](key);
    }

    /// Get the dictionary keys
    ///
    /// @return Vector of dictionary keys
    std::vector<Key> keys() const {
        // TODO Make a keys, values, and items a "View"
        return key_list;
    }

    /// Get the dictionary values
    ///
    /// @return Vector of dictionary values
    std::vector<Value> values() const {
        return val_list;
    }

    /// Get the dictionary items as a `std::vector`
    ///
    /// @return Vector of dictionary items (key-value pairs)
    std::vector<Item<Key, Value>> items() const {
        std::vector<Item<Key, Value>> item_list;
        for (int i = 0; i < key_list.size(); ++i) {
            item_list.emplace_back(key_list[i], val_list[i]);
        }

        return item_list;
    }

    /// Returns an iterator for iterating through the dictionary.
    /// The iterator point to the beginning of the `key_list`, so that this is
    /// looped through.
    ///
    /// @return Iterator pointing to the beginning of the `key_list`
    typename std::vector<Key>::iterator begin() {
        return key_list.begin();
    }

    /// Returns an iterator for iterating through a `const` dictionary.
    ///
    /// @return Iterator pointing to the `const` key at the beginning of `key_list`
    typename std::vector<const Key>::iterator begin() const {
        return key_list.begin();
    }

    /// Returns a (non-const) iterator pointing to the end of the dictionary
    ///
    /// @return Iterator pointing to the end of the `key_list`
    typename std::vector<Key>::iterator end() {
        return key_list.end();
    }

    /// Return a (const) iterator pointing to the end of the dictionary
    ///
    /// @return Iterator pointing to the end of the `const key_list`
    typename std::vector<const Key>::iterator end() const {
        return key_list.end();
    }

    // TODO Implement reversed

    /// Remove key from dictionary
    ///
    /// @throws std::out_of_range If key not in dictionary
    void del(const Key &key) {
        if (!contains(key)) {
            throw std::out_of_range("Key not found in dictionary");
        }

        const auto index = get_index(key);

        key_list.erase(key_list.begin() + index);
        val_list.erase(val_list.begin() + index);
    }

    /// Check if dictionary contains `key`
    ///
    /// @param key A possible key
    ///
    /// @return Whether key is present in dictionary
    bool contains(const Key &key) const {
        return key_exists(key);
    }

    /// Remove all items from the dictionary
    void clear() {
        key_list = {};
        val_list = {};
    }

    /// Creates a copy of the dictionary
    ///
    /// @return Exact copy of the dictionary
    Dict copy() const {
        auto new_dict = Dict();
        new_dict.key_list = key_list;
        new_dict.val_list = val_list;
        return new_dict;
    }

    /// Get value from dictionary at key `key`
    /// If the key is not present, the function returns the optional `default_value`,
    /// if this does not exist an error is thrown.
    ///
    /// @param key Dictionary key
    /// @param default_value Optional default (default: `std::nullopt`)
    ///
    /// @throws std::runtime_error If key not in dictionary and no default value is specified
    ///
    /// @return Value at key, if present, default value otherwise
    Value get(const Key &key, const std::optional<Value> &default_value = std::nullopt) const {
        if (key_exists(key)) {
            const auto idx = get_index(key);
            return val_list[idx];
        }

        if (!default_value) {
            throw std::runtime_error("Key not found in dictionary and no default exists");
        }

        return default_value.value();
    }

    /// If the key is in the dictionary, remove it and return its value, else return the
    /// default value. If no default value is given, an error is thrown.
    ///
    /// @param key The dictionary key
    /// @param default_value Optional default value (default: `std::nullopt`)
    ///
    /// @throws std::runtime_error If key not in dictionary and no default value
    ///
    /// @return Value at key in dictionary if it exists, otherwise the default.
    Value pop(const Key &key, const std::optional<Value> &default_value = std::nullopt) {
        if (key_exists(key)) {
            const auto idx = get_index(key);
            const auto value = val_list[idx];

            del(key);

            return value;
        }

        if (!default_value) {
            throw std::runtime_error("Key not found in dictionary and no default exists");
        }

        return default_value.value();
    }

    /// Remove and return the last key-value pair from the dictionary.
    ///
    /// @throws std::out_of_range If dictionary is empty
    ///
    /// @return Key-value pair
    Item<Key, Value> popitem() {
        if (empty()) {
            throw std::out_of_range("Dictionary is empty, no items to pop!");
        }
        const auto key = key_list.back();
        const auto value = pop(key);

        return {key, value};
    }

    /// If key is in the dictionary, return its value.
    /// Otherwise, insert key with value of `default_value` and return it.
    /// If default value is not set, the default constructor for `Value` is used
    /// and the value returned.
    ///
    /// @param key Dictionary key
    /// @param default_value Default value to be used (default: `std::nullopt`)
    ///
    /// @return Value at key or default.
    Value setdefault(const Key &key, const std::optional<Value> &default_value = std::nullopt) {
        if (key_exists(key)) {
            return at(key);
        }


        key_list.emplace_back(key);
        const Value value = default_value ? default_value.value() : Value();
        val_list.emplace_back(value);

        return value;
    }

    /// Updates the dictionary with key/value pairs from `other`.
    ///
    /// @param other Another dictionary
    void update(const Dict &other) {
        for (const auto &[k, v]: other.items()) {
            at(k) = v;
        }
    }

    /// Updates the dictionary with key/value pairs from a list
    ///
    /// @param pairs A list of key-value pairs
    void update(const std::initializer_list<Item<Key, Value>> &pairs) {
        for (const auto &[k, v]: pairs) {
            at(k) = v;
        }
    }

    /// Updates the dictionary with key/value pairs from a vector
    ///
    /// @param pairs A list of key-value pairs
    void update(const std::vector<Item<Key, Value>> &pairs) {
        for (const auto &[k, v]: pairs) {
            at(k) = v;
        }
    }


    /// Create a new dictionary with merged keys from `this` and `other`.
    /// The values of `other` take priority when they share keys.
    ///
    /// @param other Dictionary
    ///
    /// @return Dictionary which merges `this` and `other`
    Dict operator|(const Dict &other) const {
        auto dict = copy();
        dict.update(other);

        return dict;
    }

    /// Updates dictionary with values from another. Wrapper for `update()`
    ///
    /// @param other Another dictionary
    void operator|=(const Dict &other) {
        update(other);
    }

    /// Updates dictionary with values from initializer list. Wrapper for `update()`
    ///
    /// @param list An list of key-value pairs
    void operator|=(const std::initializer_list<Item<Key, Value>> &list) {
        update(list);
    }

    /// Update dictionary with values from vector. Wrapper for `update()`
    ///
    /// @param key_values A vector of key-value pairs
    void operator|=(const std::vector<Item<Key, Value>> &key_values) {
        update(key_values);
    }
};

// TODO Template specialisation for Value `bool`
// TODO Add map constructor, converter and updater

}

#endif //DICTCPP_HPP
