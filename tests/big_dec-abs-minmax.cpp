#include <gtest/gtest.h>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

TEST(BigDecAbs, Abs) {
  EXPECT_EQ(BigDec().Abs(), BigDec());
  EXPECT_EQ(BigDec(BigInt(-1), BigInt(3)).Abs(), BigDec(BigInt(1), BigInt(3)));
  EXPECT_EQ(BigDec(BigInt(1), BigInt(-3)).Abs(), BigDec(BigInt(1), BigInt(3)));
  EXPECT_EQ(BigDec(BigInt(1), BigInt(3)).Abs(), BigDec(BigInt(1), BigInt(3)));
  EXPECT_FALSE(BigDec(-5).Abs().IsNegative());
}

TEST(BigDecMinMax, MaxAndMin) {
  auto const a = BigDec(BigInt(-1), BigInt(3)); // -0.333...
  auto const b = BigDec(BigInt(1), BigInt(4));  //  0.25

  EXPECT_EQ(a.Max(b), b);
  EXPECT_EQ(b.Max(a), b);
  EXPECT_EQ(a.Min(b), a);
  EXPECT_EQ(b.Min(a), a);
  EXPECT_EQ(a.Max(a), a);

  // Same sign, different denominators: 2/3 > 3/5.
  EXPECT_EQ(BigDec(BigInt(2), BigInt(3)).Max(BigDec(BigInt(3), BigInt(5))), BigDec(BigInt(2), BigInt(3)));
  EXPECT_EQ(BigDec(BigInt(2), BigInt(3)).Min(BigDec(BigInt(3), BigInt(5))), BigDec(BigInt(3), BigInt(5)));
}
