#include <gtest/gtest.h>
#include "hashtable.hpp"

/*
(Comment)
Mostly worked test driven. Bodies try to conform to AAA pattern.
*/

TEST(HashTableTest, DefaultHashFunctionReturnsZero) {
  const auto actual {HashTable::linearProbeHasher("abc")};

  constexpr auto expected{0};
  EXPECT_EQ(expected, actual);
}

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