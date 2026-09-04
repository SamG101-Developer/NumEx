#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { a, b, "1" when a > b }
  auto const pairs = std::vector<std::vector<std::string>>{
    {"500000000000000000000/200000000000000000000000000", "50000000004000000000000/400000000000000000000", "0"},
    {"537483929/484588458292993", "543563/24994884934885", "1"},
    {"2/3", "6/11", "1"},
    {"2/3", "2/3", "0"},
    {"-2/3", "6/-11", "0"},
  };

  // <, >, <= and >= are all rewritten from operator<=>, so every row checks all four.
  auto checkOrdering(BigDec const &a, BigDec const &b, bool const greater) -> void {
    auto const equal = (a == b);
    EXPECT_EQ(a > b, greater);
    EXPECT_EQ(a <= b, !greater);
    EXPECT_EQ(a < b, !greater && !equal);
    EXPECT_EQ(a >= b, greater || equal);
  }
}

TEST(BigDecComparison, Positives) {
  for (auto const &s : pairs) {
    checkOrdering(BigDec(s[0]), BigDec(s[1]), s[2] != "0");
  }
}

TEST(BigDecComparison, Negated) {
  for (auto const &s : pairs) {
    auto const a = -BigDec(s[0]);
    auto const b = -BigDec(s[1]);
    // Negating both operands reverses the order, except where they are equal.
    checkOrdering(a, b, s[2] == "0" && !(a == b));
  }
}
