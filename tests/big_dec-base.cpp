#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

namespace {
  // { value in its own base, same value in decimal, same value in base 32 }
  auto const values = std::vector<std::vector<std::string>>{
    {"453453a::32/43453b::32", "4466021482/137499755", "453453a::32/43453b::32"},
    {"-453453a::32/-45afA3a::62", "171770057/8920503206", "53q069::32/89r84t6::32"},
    {"1:12:20:111::150/1:12:20:112::150", "3648111/3648112", "3fajf::32/3fajg::32"},
  };
}

TEST(BigDecBase, Decimal) {
  for (auto const &s : values) {
    EXPECT_EQ(BigDec(s[0]).ToString(), s[1]);
  }
}

TEST(BigDecBase, Base32) {
  for (auto const &s : values) {
    EXPECT_EQ(BigDec(s[0]).Base(32), s[2]);
  }
}
