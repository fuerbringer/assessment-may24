#include "hashtable.hpp"
#include <iostream>
#include <cmath>

namespace
{
bool is_cell_free_at_index(const size_t index, const HashTable::ValueTableType& table) {
  return !table[index].has_value();
}
bool is_cell_free_or_same_at_index(const size_t index, const KeyType key, const HashTable::ValueTableType& values, const HashTable::KeyTableType& keys) {
  return is_cell_free_at_index(index, values) || (keys[index] == key);
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
  const auto indexWithoutCollision{linear_probe_find_free(index, key)};
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
  Unimplemented, I don't have the time. But it would work as follows:
  Create a queue (FIFO) of indices, delete remove()ed ones. 
  First out the queue is what this function should return.
  */
  return std::nullopt;
}

void HashTable::print_contents() const {
  size_t index{0};
  for(const auto& cell : m_values) {
    if(cell.has_value()) {
      std::cout << m_keys[index].value() << ": " << cell.value() << std::endl;
    }
    index++;
  }
}

size_t HashTable::default_hash_function(KeyType key)
{
  /*
  (Comment)
  polinomial rolling hash
  potential for optimization here
  */
  constexpr auto p{31};
  const int m = std::pow(10, 9) + 9;
  const auto n{key.length()};
  int sum{0};
  for(auto i{0}; i < n; i++) {
    sum += key[i] * static_cast<int>(std::pow(p, i));
  }
  const auto index = sum % m;
  const auto indexWithinTable{index % TABLE_SIZE};
  return indexWithinTable;
}

std::optional<size_t> HashTable::linear_probe_find_free(const size_t startingIndex, const KeyType key)
{
  size_t index{startingIndex};
  if (is_cell_free_or_same_at_index(index, key, m_values, m_keys))
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
  If we were to improve performance, it would be here and the hashing function.
  Less collisions => less need to linearly probe.
  */
  auto linearProbingIndex{(index + 1) % TABLE_SIZE};
  constexpr auto maxSearchCount{TABLE_SIZE};
  bool found{false};
  for (auto i{0}; i < maxSearchCount; i++)
  {
    if (is_cell_free_or_same_at_index(linearProbingIndex, key, m_values, m_keys))
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

  /* (Comment) if we get here, then table full. No integer meaningful: */
  return std::nullopt;
}

/*
(Comment)
find_used has code duplication with find_free, could be refactored
*/
std::optional<size_t> HashTable::linear_probe_find_used(const size_t startingIndex, const KeyType key)
{
  size_t index{startingIndex};
  if (is_cell_free_or_same_at_index(index, key, m_values, m_keys))
  {
    return index;
  }

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
      } else
      {
        linearProbingIndex = (linearProbingIndex + 1) % TABLE_SIZE;
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

  return std::nullopt;
}