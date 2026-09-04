#include <gtest/gtest.h>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  auto frac(std::int64_t const num, std::int64_t const den) -> BigDec {
    return BigDec(BigInt(num), BigInt(den));
  }
}

TEST(BigDecRounding, Trunc) {
  EXPECT_EQ(frac(0, 1).Trunc(), BigInt(0));
  EXPECT_EQ(frac(7, 2).Trunc(), BigInt(3));
  EXPECT_EQ(frac(-7, 2).Trunc(), BigInt(-3));
  EXPECT_EQ(frac(1, 3).Trunc(), BigInt(0));
  EXPECT_EQ(frac(-1, 3).Trunc(), BigInt(0));
  EXPECT_EQ(frac(8, 2).Trunc(), BigInt(4)); // exact, simplifies to 4/1
}

TEST(BigDecRounding, Floor) {
  EXPECT_EQ(frac(7, 2).Floor(), BigInt(3));
  EXPECT_EQ(frac(-7, 2).Floor(), BigInt(-4));
  EXPECT_EQ(frac(1, 3).Floor(), BigInt(0));
  EXPECT_EQ(frac(-1, 3).Floor(), BigInt(-1));
  EXPECT_EQ(frac(-8, 2).Floor(), BigInt(-4)); // exact, so no step back
  EXPECT_EQ(frac(0, 5).Floor(), BigInt(0));
}

TEST(BigDecRounding, Ceil) {
  EXPECT_EQ(frac(7, 2).Ceil(), BigInt(4));
  EXPECT_EQ(frac(-7, 2).Ceil(), BigInt(-3));
  EXPECT_EQ(frac(1, 3).Ceil(), BigInt(1));
  EXPECT_EQ(frac(-1, 3).Ceil(), BigInt(0));
  EXPECT_EQ(frac(8, 2).Ceil(), BigInt(4)); // exact, so no step forward
  EXPECT_EQ(frac(0, 5).Ceil(), BigInt(0));
}

TEST(BigDecRounding, Round) {
  EXPECT_EQ(frac(1, 3).Round(), BigInt(0));
  EXPECT_EQ(frac(2, 3).Round(), BigInt(1));
  EXPECT_EQ(frac(-1, 3).Round(), BigInt(0));
  EXPECT_EQ(frac(-2, 3).Round(), BigInt(-1));

  // Halfway cases go away from zero.
  EXPECT_EQ(frac(1, 2).Round(), BigInt(1));
  EXPECT_EQ(frac(-1, 2).Round(), BigInt(-1));
  EXPECT_EQ(frac(7, 2).Round(), BigInt(4));
  EXPECT_EQ(frac(-7, 2).Round(), BigInt(-4));
  EXPECT_EQ(frac(5, 2).Round(), BigInt(3));
  EXPECT_EQ(frac(-5, 2).Round(), BigInt(-3));

  EXPECT_EQ(frac(4, 2).Round(), BigInt(2)); // exact
}

TEST(BigDecRounding, MultiLimb) {
  // 2^64 + 1 over 2, i.e. a value whose parts span more than one limb.
  auto const a = BigDec(BigInt("18446744073709551617"), BigInt(2));
  EXPECT_EQ(a.Trunc(), BigInt("9223372036854775808"));
  EXPECT_EQ(a.Floor(), BigInt("9223372036854775808"));
  EXPECT_EQ(a.Ceil(), BigInt("9223372036854775809"));
  EXPECT_EQ(a.Round(), BigInt("9223372036854775809"));

  auto const b = -a;
  EXPECT_EQ(b.Trunc(), BigInt("-9223372036854775808"));
  EXPECT_EQ(b.Floor(), BigInt("-9223372036854775809"));
  EXPECT_EQ(b.Ceil(), BigInt("-9223372036854775808"));
  EXPECT_EQ(b.Round(), BigInt("-9223372036854775809"));
}
