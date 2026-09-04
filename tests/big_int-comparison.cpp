#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { a, b, "1" when a > b }
  auto const pairs = std::vector<std::vector<std::string>>{
    {"-3235345345345", "-2935107723423", "0"},
    {"-2135107723423", "-2935107723423", "1"},
    {"3235345345345", "2935107723423", "1"},
    {"2135107723423", "2935107723423", "0"},
    {"18446744073709551616", "18446744073709551616", "0"}, // equal, spanning two limbs
    {"36893488147419103232", "18446744073709551616", "1"},
    {"-18446744073709551616", "18446744073709551616", "0"},
  };

  // <, >, <= and >= are all rewritten from operator<=>, so every row checks all four.
  auto checkOrdering(BigInt const &a, BigInt const &b, bool const greater) -> void {
    auto const equal = (a == b);
    EXPECT_EQ(a > b, greater);
    EXPECT_EQ(a <= b, !greater);
    EXPECT_EQ(a < b, !greater && !equal);
    EXPECT_EQ(a >= b, greater || equal);
    EXPECT_EQ(a != b, !equal);
  }
}

TEST(BigIntComparison, Pairs) {
  for (auto const &s : pairs) {
    checkOrdering(BigInt(s[0]), BigInt(s[1]), s[2] != "0");
  }
}

TEST(BigIntComparison, Negated) {
  for (auto const &s : pairs) {
    auto const a = -BigInt(s[0]);
    auto const b = -BigInt(s[1]);
    // Negating both operands reverses the order, except where they are equal.
    checkOrdering(a, b, s[2] == "0" && !(a == b));
  }
}

// The int64_t comparisons are members, so the compiler synthesises the reversed
// forms; these check both operand orders agree.
TEST(BigIntComparison, AgainstInt64) {
  auto const a = BigInt(42);
  EXPECT_TRUE(a == 42);
  EXPECT_TRUE(42 == a);
  EXPECT_TRUE(a != 43);
  EXPECT_TRUE(43 != a);
  EXPECT_TRUE(a > 41);
  EXPECT_TRUE(41 < a);
  EXPECT_TRUE(a < 43);
  EXPECT_TRUE(43 > a);
  EXPECT_TRUE(a >= 42);
  EXPECT_TRUE(42 <= a);
}

TEST(BigIntComparison, NegativeAgainstInt64) {
  auto const a = BigInt(-5);
  EXPECT_TRUE(a < 0);
  EXPECT_TRUE(0 > a);
  EXPECT_TRUE(a < -4);
  EXPECT_TRUE(-4 > a);
  EXPECT_TRUE(a > -6);
  EXPECT_TRUE(-6 < a);
}

// A value too wide for one limb must still compare correctly against a scalar.
TEST(BigIntComparison, MultiLimbAgainstInt64) {
  auto const big = BigInt("18446744073709551616"); // 2^64
  EXPECT_TRUE(big > 0);
  EXPECT_TRUE(0 < big);
  EXPECT_TRUE(big != 0);
  EXPECT_TRUE(-big < 0);
  EXPECT_TRUE(0 > -big);
  EXPECT_TRUE(-big < big);
}