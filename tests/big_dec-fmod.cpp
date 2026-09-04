#include <gtest/gtest.h>
#include <cstdint>
#include <stdexcept>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  auto frac(std::int64_t const num, std::int64_t const den) -> BigDec {
    return BigDec(BigInt(num), BigInt(den));
  }
}

TEST(BigDecFmod, Integers) {
  EXPECT_EQ(BigDec(7).Fmod(BigDec(2)), BigDec(1));
  EXPECT_EQ(BigDec(-7).Fmod(BigDec(2)), BigDec(-1));
  EXPECT_EQ(BigDec(7).Fmod(BigDec(-2)), BigDec(1));
  EXPECT_EQ(BigDec(-7).Fmod(BigDec(-2)), BigDec(-1));
  EXPECT_EQ(BigDec(8).Fmod(BigDec(2)), BigDec(0));
}

TEST(BigDecFmod, Fractions) {
  // 1/2 fits into 1/3 once, leaving 1/6.
  EXPECT_EQ(frac(1, 2).Fmod(frac(1, 3)), frac(1, 6));
  EXPECT_EQ(frac(-1, 2).Fmod(frac(1, 3)), frac(-1, 6));
  EXPECT_EQ(frac(1, 2).Fmod(frac(-1, 3)), frac(1, 6));
  EXPECT_EQ(frac(-1, 2).Fmod(frac(-1, 3)), frac(-1, 6));

  // A divisor larger than the dividend leaves the dividend untouched.
  EXPECT_EQ(frac(1, 3).Fmod(frac(1, 2)), frac(1, 3));
  EXPECT_EQ(frac(-1, 3).Fmod(frac(1, 2)), frac(-1, 3));

  // Exact multiples leave nothing behind.
  EXPECT_EQ(frac(3, 4).Fmod(frac(1, 4)), BigDec(0));
  EXPECT_EQ(frac(-3, 4).Fmod(frac(1, 4)), BigDec(0));

  EXPECT_EQ(BigDec(0).Fmod(frac(1, 3)), BigDec(0));
}

TEST(BigDecFmod, IsExactAndSmallerThanTheDivisor) {
  auto const cases = std::vector<std::pair<BigDec, BigDec>>{
    {frac(22, 7), frac(1, 3)},
    {frac(-22, 7), frac(1, 3)},
    {frac(22, 7), frac(-1, 3)},
    {frac(-22, 7), frac(-1, 3)},
    {BigDec(BigInt("18446744073709551617"), BigInt(3)), frac(5, 7)},
  };

  for (auto const &[a, b] : cases) {
    auto const r = a.Fmod(b);

    // fmod is exact: a == trunc(a / b) * b + r, with r under b in magnitude.
    auto const quot = BigDec((a / b).Trunc(), BigInt(1));
    EXPECT_EQ(quot * b + r, a);
    EXPECT_TRUE(r.Abs() < b.Abs());

    // The remainder never contradicts the dividend's sign.
    if (r != 0) EXPECT_EQ(r.IsNegative(), a.IsNegative());
  }
}

TEST(BigDecFmod, ByZeroThrows) {
  EXPECT_THROW((void) BigDec(1).Fmod(BigDec(0)), std::invalid_argument);
  EXPECT_THROW((void) BigDec(0).Fmod(BigDec(0)), std::invalid_argument);
}
