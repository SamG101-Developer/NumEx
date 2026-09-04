#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { value in its own base, same value in decimal, same value in base 36 }
  auto const values = std::vector<std::vector<std::string>>{
    {"453453a::32", "4466021482", "21uyc8a::36"},
    {"-453453a::32", "-4466021482", "-21uyc8a::36"},
    {"cc453453a::32", "13610922415210", "4torrs60a::36"},
    {"cc45A3453a::50", "23909464394262660", "6jf74b49m6c::36"},
    {"0::150", "0", "0::36"},
    {"1::150", "1", "1::36"},
    {"1:12::150", "162", "4i::36"},
    {"1:12:20::150", "24320", "irk::36"},
    {"1:12:20:111::150", "3648111", "266wf::36"},
    {"1:1::150", "151", "47::36"},
    {"1:1:1::150", "22651", "hh7::36"},
  };
}

TEST(BigIntBase, FromBaseToDecimal) {
  for (auto const &s : values) {
    EXPECT_EQ(BigInt(s[0]).ToString(), s[1]);
  }
}

TEST(BigIntBase, FromDecimalToBase36) {
  for (auto const &s : values) {
    EXPECT_EQ(BigInt(s[1]).Base(36), s[2]);
  }
}
