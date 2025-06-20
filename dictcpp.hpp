#ifndef DICTCPP_HPP
#define DICTCPP_HPP
#include <set>
#include <vector>

namespace dictcpp {
template<typename Key, typename Value = Key>
struct Item {
    Key key;
    Value value;
};

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
    // Initialise an empty dictionary
    Dict(): key_list({}), val_list({}) {
    }

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

    [[nodiscard]] bool empty() const {
        return key_list.empty();
    }

    [[nodiscard]] size_t size() const {
        return key_list.size();
    }

    const Value &operator[](const Key &key) const {
        if (!key_exists(key)) {
            throw std::out_of_range("Key not found in dictionary");
        }

        return val_list[get_index(key)];
    }

    Value &operator[](const Key &key) {
        if (key_exists(key)) {
            const auto index = get_index(key);

            return val_list[index];
        }

        key_list.push_back(key);
        val_list.push_back(Value());

        return val_list.back();
    }

    Value &at(const Key &key) {
        return operator[](key);
    }

    const Value &at(const Key &key) const {
        return operator[](key);
    }

    std::vector<Key> keys() const {
        return key_list;
    }

    std::vector<Value> values() const {
        return val_list;
    }

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
