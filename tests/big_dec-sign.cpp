#include <gtest/gtest.h>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

TEST(BigDecSign, IsNegative) {
  EXPECT_FALSE(BigDec().IsNegative());
  EXPECT_FALSE(BigDec(3).IsNegative());
  EXPECT_TRUE(BigDec(-3).IsNegative());

  // A negative denominator is normalised onto the numerator by _Simplify().
  EXPECT_TRUE(BigDec(BigInt(1), BigInt(-2)).IsNegative());
  EXPECT_TRUE(BigDec(BigInt(-1), BigInt(2)).IsNegative());
  EXPECT_FALSE(BigDec(BigInt(-1), BigInt(-2)).IsNegative());

  EXPECT_TRUE(BigDec("-1/3").IsNegative());
  EXPECT_TRUE((BigDec(BigInt(1), BigInt(3)) - BigDec(BigInt(2), BigInt(3))).IsNegative());
  EXPECT_FALSE((BigDec(BigInt(-1), BigInt(3)) * BigDec(BigInt(-1), BigInt(3))).IsNegative());
}
