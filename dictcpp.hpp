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

    /// Initialise a dictionary using a vector of `Item`s.
    ///
    /// @param key_values A vector where each element is a dictionary `Item` (key-value pair)
    explicit Dict(const std::vector<Item<Key, Value>> &key_values) : key_list(), val_list() {
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
        val_list.push_back(Value());

        return val_list.back();
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
        return key_list;
    }

    /// Get the dictionary values
    ///
    /// @return Vector of dictionary values
    std::vector<Value> values() const {
        return val_list;
    }

    /// Get the dictionary items as a `std::vector<Item>`
    ///
    /// @return Vector of dictionary items (key-value pairs)
    std::vector<Item<Key, Value>> items() const {
        std::vector<Item<Key, Value>> item_list;
        for (int i = 0; i < key_list.size(); ++i) {
            item_list.emplace_back(key_list[i], val_list[i]);
        }

        return item_list;
    }
};
}

#endif //DICTCPP_HPP
