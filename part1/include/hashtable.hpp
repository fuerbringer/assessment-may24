#pragma once

#include "hashtableinterface.hpp"
#include <array>
#include <functional>
#include <optional>

/*
(Comment)
Hashing function can be passed to hash table to enable any type of hashing method
Saving keeps track of keys so it can find cell values that were placed when linear probing tried to fix their colliding keys.
*/
using HashFunction = std::function<size_t(KeyType)>;

class HashTable : public HashTableInterface {
public:
    HashTable();
    HashTable(HashFunction hashFunction);
public:
    bool insert(KeyType key, ValueType value);
    void remove(KeyType key);
    std::optional<ValueType> get(KeyType key);
    std::optional<ValueType> get_last() const;
    std::optional<ValueType> get_first() const;
    void print_contents() const;

    static constexpr size_t TABLE_SIZE{500};
    static inline const KeyType EMPTY_KEY{""};
    static inline const ValueType EMPTY_VALUE{0};
    size_t default_hash_function(KeyType);
    using KeyTableType = std::array<std::optional<KeyType>, HashTable::TABLE_SIZE>;
    using ValueTableType = std::array<std::optional<ValueType>, HashTable::TABLE_SIZE>;
private:
    KeyTableType m_keys{};
    ValueTableType m_values{};
    HashFunction m_hashFunction{};
    std::optional<size_t> m_mostRecentlyMutated{};
    std::optional<size_t> linear_probe_find_free(size_t index, const KeyType key);
    std::optional<size_t> linear_probe_find_used(size_t index, KeyType key);
};