#include "hashtable.hpp"
#include <iostream>

namespace
{
bool is_cell_fee_at_index(const size_t index, const HashTable::ValueTableType& table) {
  return !table[index].has_value();
}
}

HashTable::HashTable() 
{
  m_hashFunction = std::bind(&HashTable::default_hash_function, this, std::placeholders::_1);
}

HashTable::HashTable(HashFunction hashFunction)
{
  m_hashFunction = hashFunction;
}

bool HashTable::insert(const KeyType key, const ValueType value)
{
  const auto index{m_hashFunction(key)};
  const auto indexWithoutCollision{linear_probe_find_free(index)};
  if(!indexWithoutCollision.has_value()) {
    return false;
  }
  const auto tableIndex = indexWithoutCollision.value();
  m_keys[tableIndex] = key;
  m_values[tableIndex] = value;
  m_mostRecentlyMutated = tableIndex;
  return true;
}

void HashTable::remove(const KeyType key)
{
  const auto index{m_hashFunction(key)};
  const auto indexWithoutCollision{linear_probe_find_used(index, key)};
  if(indexWithoutCollision.has_value()) {
    const auto tableIndex = indexWithoutCollision.value();
    m_values[indexWithoutCollision.value()] = EMPTY_VALUE;
    m_keys[indexWithoutCollision.value()] = EMPTY_KEY;
    m_mostRecentlyMutated = tableIndex;
  }
}

std::optional<ValueType> HashTable::get(const KeyType key)
{
  const auto index{m_hashFunction(key)};
  const auto indexWithoutCollision{linear_probe_find_used(index, key)};
  if(indexWithoutCollision.has_value()) {
    return m_values[indexWithoutCollision.value()];
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

size_t HashTable::default_hash_function(KeyType key)
{
  return key.length() % TABLE_SIZE;
}

std::optional<size_t> HashTable::linear_probe_find_free(const size_t startingIndex)
{
  size_t index{startingIndex};
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

std::optional<size_t> HashTable::linear_probe_find_used(const size_t startingIndex, const KeyType key)
{
  size_t index{startingIndex};
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
    if(m_keys[linearProbingIndex].has_value()) 
    {
      if (m_keys[linearProbingIndex].value() == key)
      {
        index = linearProbingIndex;
        found = true;
      }
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