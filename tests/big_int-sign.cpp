#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

import numex.big_int;

using numex::BigInt;

TEST(BigIntSign, IsNegative) {
  EXPECT_FALSE(BigInt(0).IsNegative());
  EXPECT_FALSE(BigInt(1).IsNegative());
  EXPECT_TRUE(BigInt(-1).IsNegative());
  EXPECT_TRUE(BigInt(std::numeric_limits<std::int64_t>::min()).IsNegative());
  EXPECT_FALSE(BigInt(std::numeric_limits<std::int64_t>::max()).IsNegative());

  // Values spanning more than one limb.
  EXPECT_FALSE(BigInt("18446744073709551616").IsNegative());
  EXPECT_TRUE(BigInt("-18446744073709551616").IsNegative());

  // The sign tracks the value after arithmetic, including a negation back to zero.
  EXPECT_TRUE((BigInt(1) - BigInt(2)).IsNegative());
  EXPECT_FALSE((-BigInt(0)).IsNegative());
  EXPECT_FALSE((BigInt(-2) * BigInt(-2)).IsNegative());
}
