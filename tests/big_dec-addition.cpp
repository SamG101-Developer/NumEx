#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { a numerator, a denominator, b numerator, b denominator, sum numerator, sum denominator }
  auto const sums = std::vector<std::vector<std::string>>{
    {"1", "3", "1", "8", "11", "24"},
    {"2", "3", "3", "8", "25", "24"},
    {"2444234", "3434634563567456", "34563457727", "457536743223454565677473721", "559163491374441896220487035953613", "785735756188682526849306693345947725411888"},
  };
}

TEST(BigDecAddition, Positives) {
  for (auto const &s : sums) {
    auto const a = BigDec(BigInt(s[0]), BigInt(s[1]));
    auto const b = BigDec(BigInt(s[2]), BigInt(s[3]));
    auto const expected = BigDec(BigInt(s[4]), BigInt(s[5]));
    EXPECT_EQ((a + b).ToString(), expected.ToString());
  }
}

TEST(BigDecAddition, Negatives) {
  for (auto const &s : sums) {
    auto const a = BigDec(BigInt("-" + s[0]), BigInt(s[1]));
    auto const b = BigDec(BigInt(s[2]), BigInt("-" + s[3]));
    auto const expected = BigDec(BigInt("-" + s[4]), BigInt(s[5]));
    EXPECT_EQ((a + b).ToString(), expected.ToString());
  }
}
