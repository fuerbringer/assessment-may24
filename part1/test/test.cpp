#include <gtest/gtest.h>
#include "hashtable.hpp"

/*
(Comment)
Mostly worked test driven. Bodies try to conform to AAA pattern.
*/
using KeyValue = std::pair<KeyType, ValueType>;

TEST(HashTableTest, HashingFunctionFindsNothingWithRandomKeyInEmptyTable) {
  HashTable emptyHashTable{};

  const auto randomkey{"Charles"};
  const auto actual {emptyHashTable.default_hash_function(randomkey)};

  EXPECT_EQ(7, actual);
}

TEST(HashTableTest, EmptyHashTableHasNothingForRandomKey) {
  HashTable emptyHashTable{};

  const auto randomkey{"Dickens"};
  const auto actual{emptyHashTable.get(randomkey)};

  EXPECT_FALSE(actual.has_value());
}

TEST(HashTableTest, RandomPairInsertedIntoEmptyHashTableWorks) {
  HashTable hashTable{};

  const KeyValue pair{"The", 300};
  const auto success{hashTable.insert(pair.first, pair.second)};

  EXPECT_TRUE(success);
}

TEST(HashTableTest, PairInsertedTwiceIntoEmptyHashTableWorks) {
  HashTable hashTable{};

  const KeyValue pair{"The", 300};
  hashTable.insert(pair.first, pair.second);
  const auto success{hashTable.insert(pair.first, pair.second)};

  EXPECT_TRUE(success);
}

TEST(HashTableTest, PairInsertedAfterTableFullFails) {
  HashTable hashTable{};

  const KeyValue pair{"abc", 2};
  for(auto i{0}; i < HashTable::TABLE_SIZE; i++) {
    hashTable.insert(pair.first, pair.second);
  }
  const auto success {hashTable.insert(pair.first, pair.second)};

  EXPECT_FALSE(success);
}

TEST(HashTableTest, InsertedPairIsFoundWithGet) {
  HashTable hashTable{};
  const KeyValue pair{"def", 9};
  hashTable.insert(pair.first, pair.second);

  const auto success{hashTable.get(pair.first)};

  EXPECT_TRUE(success.has_value());
}

TEST(HashTableTest, GetReturnsCorrectValueForInsertedPair) {
  HashTable hashTable{};
  const KeyValue pair{"def", 9};
  hashTable.insert(pair.first, pair.second);

  const auto success{hashTable.get(pair.first)};

  EXPECT_EQ(9, success.value());
}

TEST(HashTableTest, DifferentKeyValuePairsInsertedOneRemovedCantBeFoundAgain) {
  HashTable hashTable{};
  const KeyValue pair{"123", 4};
  const KeyValue pair2{"456", 8};
  hashTable.insert(pair.first, pair.second);
  hashTable.insert(pair2.first, pair2.second);
  hashTable.remove(pair.first);

  const auto success{hashTable.get(pair.first)};

  EXPECT_FALSE(success);
}

TEST(HashTableTest, DifferentKeyValuePairsInsertedOneRemovedFirstCantBeFoundAgain) {
  HashTable hashTable{};
  const KeyValue pair{"123", 4};
  const KeyValue pair2{"456", 8};
  hashTable.insert(pair.first, pair.second);
  hashTable.insert(pair2.first, pair2.second);
  hashTable.remove(pair2.first);

  const auto success{hashTable.get(pair2.first)};

  EXPECT_FALSE(success);
}

/*
TEST(HashTableTest, GetReturnsZero) {
  HashTable hashTable{};

  const auto key{"123"};
  const auto actual{hashTable.get(key)};

  constexpr auto expected{""};
  EXPECT_EQ(expected, actual);
}

TEST(HashTableTest, GetReturnsEmpty) {
  HashTable hashTable{};

  const auto key{"123"};
  const auto actual{hashTable.get(key)};

  constexpr auto expected{""};
  EXPECT_EQ(expected, actual);
}

TEST(HashTableTest, GetLastReturnsEmpty) {
  HashTable hashTable{};

  const auto actual{hashTable.get_last()};

  constexpr auto expected{""};
  EXPECT_EQ(expected, actual);
}

TEST(HashTableTest, GetFirstReturnsEmpty) {
  HashTable hashTable{};

  const auto actual{hashTable.get_first()};

  constexpr auto expected{""};
  EXPECT_EQ(expected, actual);
}
*/