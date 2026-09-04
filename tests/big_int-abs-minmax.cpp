#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <string>

import numex.big_int;

using numex::BigInt;

TEST(BigIntAbs, Abs) {
  EXPECT_EQ(BigInt(0).Abs(), BigInt(0));
  EXPECT_EQ(BigInt(7).Abs(), BigInt(7));
  EXPECT_EQ(BigInt(-7).Abs(), BigInt(7));

  // Magnitudes that do not fit a signed limb, so negating widens the number.
  EXPECT_EQ(BigInt("-18446744073709551616").Abs(), BigInt("18446744073709551616"));
  EXPECT_EQ(BigInt(std::numeric_limits<std::int64_t>::min()).Abs(), BigInt("9223372036854775808"));

  EXPECT_FALSE(BigInt(-7).Abs().IsNegative());
}

TEST(BigIntMinMax, MaxAndMin) {
  auto const a = BigInt(-4);
  auto const b = BigInt(9);

  EXPECT_EQ(a.Max(b), b);
  EXPECT_EQ(b.Max(a), b);
  EXPECT_EQ(a.Min(b), a);
  EXPECT_EQ(b.Min(a), a);

  // Equal operands, and multi-limb operands compared across sizes.
  EXPECT_EQ(a.Max(a), a);
  EXPECT_EQ(a.Min(a), a);
  EXPECT_EQ(BigInt("18446744073709551616").Max(BigInt(1)), BigInt("18446744073709551616"));
  EXPECT_EQ(BigInt("-18446744073709551616").Min(BigInt(-1)), BigInt("-18446744073709551616"));
}
