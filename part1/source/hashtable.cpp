#include "hashtable.hpp"
#include <iostream>

namespace
{
bool is_cell_fee_at_index(const size_t index, const HashTable::TableType& table) {
  return !table[index].has_value();
}
}

HashTable::HashTable() 
{
  m_hashFunction = std::bind(&HashTable::linear_probe_hasher, this, std::placeholders::_1);
}

HashTable::HashTable(HashFunction hashFunction)
{
  m_hashFunction = hashFunction;
}

bool HashTable::insert(const KeyType key, const ValueType value)
{
  const auto index{m_hashFunction(key)};
  if(!index.has_value()) {
    return false;
  }
  const auto tableIndex = index.value();
  m_values[tableIndex] = value;
  m_mostRecentlyMutated = tableIndex;
  return true;
}

void HashTable::remove(const KeyType key)
{
  const auto index{m_hashFunction(key)};
  if(index.has_value()) {
    const auto tableIndex = index.value();
    m_values[index.value()] = EMPTY_VALUE;
    m_mostRecentlyMutated = tableIndex;
  }
}

std::optional<ValueType> HashTable::get(const KeyType key)
{
  const auto index{m_hashFunction(key)};
  if(index.has_value()) {
    return m_values[index.value()];
  }
  return std::nullopt;
}

std::optional<ValueType> HashTable::get_last() const
{
  if(m_mostRecentlyMutated.has_value()) {
    return m_values[m_mostRecentlyMutated.value()];
  }
  return std::nullopt;
}

std::optional<ValueType> HashTable::get_first() const {
  /*
  (Comment)
  TODO keep track of LRU
  */
  return std::nullopt;
}

void HashTable::debug_print_content() const {
  size_t index{0};
  for(const auto& cell : m_values) {
    if(cell.has_value()) {
      std::cout << index << ": " << cell.value() << std::endl;
    }
  }
}

std::optional<size_t> HashTable::linear_probe_hasher(KeyType key)
{
  auto index{key.length() % TABLE_SIZE};
  if (is_cell_fee_at_index(index, m_values))
  {
    /*
    (Comment)
    O(1)
    */
    return index;
  }

  /*
  (Comment)
  from here, it's linear probing, O(n)
  */
  auto linearProbingIndex{(index + 1) % TABLE_SIZE};
  constexpr auto maxSearchCount{TABLE_SIZE};
  bool found{false};
  for (auto i{0}; i < maxSearchCount; i++)
  {
    if (is_cell_fee_at_index(linearProbingIndex, m_values))
    {
      index = linearProbingIndex;
      found = true;
    }
    else
    {
      linearProbingIndex = (linearProbingIndex + 1) % TABLE_SIZE;
    }
  }
  if(found) {
    return index;
  }

  // (Comment) if we get here, then table full. No integer meaningful:
  return std::nullopt;
}