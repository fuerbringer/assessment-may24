#include <gtest/gtest.h>
#include "library.hpp"

TEST(TestGroup, BasicAssertions) {
  EXPECT_EQ(1, library());
}

