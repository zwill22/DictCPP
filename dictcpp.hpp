#ifndef DICTCPP_HPP
#define DICTCPP_HPP
#include <set>
#include <vector>

namespace dictcpp {
template<typename Key, typename Value>
class Dict {
    std::vector<Key> keys;
    std::vector<Value> values;

    size_t get_index(const Key &key) const {
        for (size_t i = 0; i < keys.size(); i++) {
            if (keys[i] == key) {
                return i;
            }
        }

        throw std::logic_error("`get_index` called but key not in dictionary");
    }

public:
    // Initialise an empty dictionary
    Dict(): keys({}), values({}) {
    }

    [[nodiscard]] bool empty() const {
        return keys.empty();
    }

    [[nodiscard]] size_t size() const {
        return keys.size();
    }

    const Value &operator[](const Key &key) const {
        if (!std::set<Key>(keys.begin(), keys.end()).contains(key)) {
            throw std::out_of_range("Key not found in dictionary");
        }

        return values[get_index(key)];
    }

    Value &operator[](const Key &key) {
        if (std::set<Key>(keys.begin(), keys.end()).contains(key)) {
            const auto index = get_index(key);

            return values[index];
        }

        keys.push_back(key);
        values.push_back(Value());

        return values.back();
    }

    Value &at(const Key &key) {
        return operator[](key);
    }

    const Value &at(const Key &key) const {
        return operator[](key);
    }
};
}

#endif //DICTCPP_HPP
