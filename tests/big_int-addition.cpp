#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { value, value + value }
  auto const doubling = std::vector<std::vector<std::string>>{
    {"2305843009213693952", "4611686018427387904"},
    {"4611686018427387904", "9223372036854775808"},
    {"9223372036854775808", "18446744073709551616"},
    {"18446744073709551616", "36893488147419103232"},
    {"36893488147419103232", "73786976294838206464"},
  };
}

TEST(BigIntAddition, Positives) {
  for (auto const &s : doubling) {
    auto const a = BigInt(s[0]);
    EXPECT_EQ((a + a).ToString(), s[1]);
  }
}

TEST(BigIntAddition, Negatives) {
  for (auto const &s : doubling) {
    auto const a = BigInt("-" + s[0]);
    EXPECT_EQ((a + a).ToString(), "-" + s[1]);
  }
}