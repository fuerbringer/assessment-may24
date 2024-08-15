#include "hashtable.hpp"

HashFunction HashTable::linearProbeHasher = [](const ValueType value) -> size_t {
  return {};
};

HashTable::HashTable(const HashFunction hashFunction) : m_hashFunction(hashFunction)
{
}

void HashTable::insert(const KeyType key, const ValueType value)
{
}

void HashTable::remove(const KeyType key)
{

}

ValueType HashTable::get(const KeyType key)
{
  return {};
}

ValueType HashTable::get_last() const
{
  return {};
}

ValueType HashTable::get_first() const {
  return {};
}