#pragma once

#include "hashtableinterface.hpp"
#include <array>
#include <functional>

using HashFunction = std::function<size_t(const ValueType)>;


class HashTable : public HashTableInterface {
public:
    HashTable(HashFunction hashFunction = linearProbeHasher);
public:
    void insert(KeyType key, ValueType value);
    void remove(KeyType key);
    ValueType get(KeyType key);
    ValueType get_last() const;
    ValueType get_first() const;

    static constexpr size_t TABLE_SIZE{1000};
    static HashFunction linearProbeHasher;
private:
    std::array<ValueType, TABLE_SIZE> m_values{};
    HashFunction m_hashFunction{};
};