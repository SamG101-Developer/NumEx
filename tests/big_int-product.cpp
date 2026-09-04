#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { value, value * value }
  auto const squares = std::vector<std::vector<std::string>>{
    {"2305843009213693952", "5316911983139663491615228241121378304"},
    {"4611686018427387904", "21267647932558653966460912964485513216"},
    {"9223372036854775808", "85070591730234615865843651857942052864"},
    {"18446744073709551616", "340282366920938463463374607431768211456"},
    {"36893488147419103232", "1361129467683753853853498429727072845824"},
  };

  auto const largePowerOfTen =
    std::string("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(BigIntProduct, NegativeTimesNegative) {
  auto const a = BigInt("-500000000000000000000000000000000000000000000000");
  auto const b = BigInt("-500000000000000000000000000000000000000000");
  EXPECT_EQ((a * b).ToString(),
    "250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(BigIntProduct, SquarePositives) {
  for (auto const &s : squares) {
    auto a = BigInt(s[0]);
    a *= a;
    EXPECT_EQ(a.ToString(), s[1]);
  }
}

TEST(BigIntProduct, SquareNegatives) {
  for (auto const &s : squares) {
    auto a = BigInt("-" + s[0]);
    a *= a;
    EXPECT_EQ(a.ToString(), s[1]);
  }
}

TEST(BigIntProduct, TimesNegativeScalar) {
  for (auto const &s : squares) {
    auto a = BigInt(s[1]);
    a *= -10;
    EXPECT_EQ(a.ToString(), "-" + s[1] + "0");
  }
}

TEST(BigIntProduct, TimesLargePowerOfTen) {
  for (auto const &s : squares) {
    auto a = BigInt("-" + s[1]);
    a *= BigInt(largePowerOfTen);
    EXPECT_EQ(a.ToString(), "-" + s[1] + largePowerOfTen.substr(1));
  }
}
