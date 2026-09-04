#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { dividend, divisor, quotient }
  auto const divisions = std::vector<std::vector<std::string>>{
    {"-500000000000000000000/200000000000000000000000000", "-50000000004000000000000/400000000000000000000", "250/12500000001"},
    {"543563/24994884934885", "-537483929/484588458292993", "-263404356155114154059/13434348959704898963165"},
  };
}

TEST(BigDecDivision, Positives) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigDec(s[0]) / BigDec(s[1])).ToString(), BigDec(s[2]).ToString());
  }
}

TEST(BigDecDivision, NegatedDivisor) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigDec(s[0]) / -BigDec(s[1])).ToString(), (-BigDec(s[2])).ToString());
  }
}
