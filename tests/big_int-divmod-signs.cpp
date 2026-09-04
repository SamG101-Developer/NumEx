#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { dividend, divisor, quotient, remainder } under truncated division: the
  // quotient rounds towards zero and the remainder keeps the dividend's sign.
  auto const rows = std::vector<std::vector<std::int64_t>>{
    {7, 2, 3, 1},
    {-7, 2, -3, -1},
    {7, -2, -3, 1},
    {-7, -2, 3, -1},
    {8, 2, 4, 0},
    {-8, 2, -4, 0},
    {8, -2, -4, 0},
    {-8, -2, 4, 0},
    // |dividend| < |divisor|, so the quotient is zero and the dividend is the remainder.
    {1, 3, 0, 1},
    {-1, 3, 0, -1},
    {1, -3, 0, 1},
    {-1, -3, 0, -1},
    {0, -3, 0, 0},
  };
}

TEST(BigIntDivModSigns, QuotientAndRemainder) {
  for (auto const &r : rows) {
    auto const a = BigInt(r[0]);
    auto const b = BigInt(r[1]);

    EXPECT_EQ(a / b, BigInt(r[2])) << r[0] << " / " << r[1];
    EXPECT_EQ(a % b, BigInt(r[3])) << r[0] << " % " << r[1];
    EXPECT_EQ(a / r[1], BigInt(r[2])) << r[0] << " / " << r[1] << " (scalar)";
    EXPECT_EQ(a % r[1], BigInt(r[3])) << r[0] << " % " << r[1] << " (scalar)";

    // The division identity has to hold for every sign combination.
    EXPECT_EQ((a / b) * b + (a % b), a) << r[0] << ", " << r[1];
  }
}

TEST(BigIntDivModSigns, MultiLimb) {
  auto const a = BigInt("-18446744073709551617"); // -(2^64 + 1)
  auto const b = BigInt("-4294967296");           // -(2^32)

  EXPECT_EQ(a / b, BigInt("4294967296"));
  EXPECT_EQ(a % b, BigInt(-1));
  EXPECT_EQ((a / b) * b + (a % b), a);

  EXPECT_EQ(a / -b, BigInt("-4294967296"));
  EXPECT_EQ(a % -b, BigInt(-1));
}
