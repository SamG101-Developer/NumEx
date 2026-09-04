#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { a, b, a * b, a * a }
  auto const products = std::vector<std::vector<std::string>>{
    {"-500000000000000000000/200000000000000000000000000", "-50000000004000000000000/400000000000000000000" , "12500000001/40000000000000", "1/160000000000"},
    {"543563/24994884934885", "-537483929/484588458292993" , "-292156376899027/12112232755806678879056760805", "295460734969/624744272908141130689963225"},
  };
}

TEST(BigDecProduct, Positives) {
  for (auto const &s : products) {
    EXPECT_EQ((BigDec(s[0]) * BigDec(s[1])).ToString(), BigDec(s[2]).ToString());
  }
}

TEST(BigDecProduct, NegatedRight) {
  for (auto const &s : products) {
    EXPECT_EQ((BigDec(s[0]) * -BigDec(s[1])).ToString(), (-BigDec(s[2])).ToString());
  }
}

TEST(BigDecProduct, SquarePositives) {
  for (auto const &s : products) {
    auto const a = BigDec(s[0]);
    EXPECT_EQ((a * a).ToString(), BigDec(s[3]).ToString());
  }
}

TEST(BigDecProduct, SquareNegatives) {
  for (auto const &s : products) {
    auto const a = -BigDec(s[0]);
    EXPECT_EQ((a * a).ToString(), BigDec(s[3]).ToString());
  }
}
