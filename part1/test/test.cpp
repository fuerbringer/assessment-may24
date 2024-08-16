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

  EXPECT_EQ(403, actual);
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

TEST(HashTableTest, DifferentPairsInsertedAfterTableFullFails) {
  HashTable hashTable{};

  KeyValue pair{"X", 2};
  for(auto i{0}; i < HashTable::TABLE_SIZE; i++) {
    hashTable.insert(std::to_string(i), 123);
  }
  const auto success {hashTable.insert(pair.first, pair.second)};

  EXPECT_FALSE(success);
}

TEST(HashTableTest, SamePairInsertedAfterTableFullWorks) {
  HashTable hashTable{};

  KeyValue pair{"X", 2};
  for(auto i{0}; i < HashTable::TABLE_SIZE; i++) {
    hashTable.insert(pair.first, pair.second);
  }
  const auto success {hashTable.insert(pair.first, pair.second)};

  EXPECT_TRUE(success);
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

TEST(HashTableTest, GetReturnsCorrectValueForInsertedPairWithOtherSameKeyInsertedAfter) {
  HashTable hashTable{};
  const KeyValue pair{"def", 9};
  const KeyValue pair2{"gop", 12};
  hashTable.insert(pair.first, pair.second);
  hashTable.insert(pair2.first, pair2.second);

  const auto result{hashTable.get(pair.first)};

  if(result.has_value()) {
    EXPECT_EQ(9, result.value());
  } else {
    FAIL();
  }
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

TEST(HashTableTest, MultiplePairsInsertedGetLastReturnsCorrectValue) {
  HashTable hashTable{};
  const KeyValue pair{"to", 0};
  const KeyValue pair2{"to", 1};
  const KeyValue pair3{"a", 999};
  hashTable.insert(pair.first, pair.second);
  hashTable.insert(pair2.first, pair2.second);
  hashTable.insert(pair2.first, pair2.second + 1);
  hashTable.insert(pair3.first, pair3.second);

  const auto result{hashTable.get_last().value()};

  EXPECT_EQ(999, result);
}

TEST(HashTableTest, SameWordFoundIncreaseOccurrenceValue) {
  HashTable hashTable{};
  const KeyValue pair{"the", 1};
  hashTable.insert(pair.first, pair.second);
  const auto occurrences {hashTable.get(pair.first).value()};
  const auto newOccurrences{occurrences + 1};

  hashTable.insert(pair.first, newOccurrences);

  const auto result{hashTable.get(pair.first).value()};

  EXPECT_EQ(2, result);
}

TEST(HashTableTest, GetFirstReturnsEmpty) {
  HashTable hashTable{};

  const auto actual{hashTable.get_first()};

  EXPECT_FALSE(actual.has_value());
}