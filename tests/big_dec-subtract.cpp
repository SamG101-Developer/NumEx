#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { a numerator, a denominator, b numerator, b denominator, difference numerator, difference denominator }
  auto const differences = std::vector<std::vector<std::string>>{
    {"1", "3", "1", "8", "5", "24"},
    {"2", "3", "3", "8", "7", "24"},
    {"3", "8", "2", "3", "-7", "24"},
    {"2", "3", "0", "8", "2", "3"},
    {"0", "3", "6", "16", "-3", "8"},
    {"2444234", "3434634563567456", "34563457727", "457536743223454565677473721", "559163372661595350663627267021101", "785735756188682526849306693345947725411888"},
  };
}

TEST(BigDecSubtract, Positives) {
  for (auto const &s : differences) {
    auto const a = BigDec(BigInt(s[0]), BigInt(s[1]));
    auto const b = BigDec(BigInt(s[2]), BigInt(s[3]));
    auto const expected = BigDec(BigInt(s[4]), BigInt(s[5]));
    EXPECT_EQ((a - b).ToString(), expected.ToString());
  }
}

TEST(BigDecSubtract, Negatives) {
  for (auto const &s : differences) {
    auto const a = -BigDec(BigInt(s[0]), BigInt(s[1]));
    auto const b = -BigDec(BigInt(s[2]), BigInt(s[3]));
    auto const expected = -BigDec(BigInt(s[4]), BigInt(s[5]));
    EXPECT_EQ((a - b).ToString(), expected.ToString());
  }
}
