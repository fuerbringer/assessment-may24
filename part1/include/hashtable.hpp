#pragma once

#include "hashtableinterface.hpp"
#include <array>
#include <functional>
#include <optional>

/*
(Comment)
Hashing function can be passed to hash table to enable any type of hashing method
*/
using HashFunction = std::function<std::optional<size_t>(KeyType)>;

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
    void debug_print_content() const;

    static constexpr size_t TABLE_SIZE{100};
    static inline const ValueType EMPTY_VALUE{0};
    std::optional<size_t> linear_probe_hasher(KeyType);
    using TableType = std::array<std::optional<ValueType>, HashTable::TABLE_SIZE>;
private:
    TableType m_values{};
    HashFunction m_hashFunction{};
    std::optional<size_t> m_mostRecentlyMutated{};
};