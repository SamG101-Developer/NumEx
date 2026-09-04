#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { a, b, a - b }
  auto const differences = std::vector<std::vector<std::string>>{
    {"-500000000000000000000", "500000000000000000000", "-1000000000000000000000"},
    {"500000000000000000000", "-500000000000000000000", "1000000000000000000000"},
    {"18446744073709551616", "1", "18446744073709551615"}, // (1 << 64) - 1,
    {"115792089237316195423570985008687907853269984665640564039457584007913129639936", "1", "115792089237316195423570985008687907853269984665640564039457584007913129639935"}, // (1 << 256) - 1,
  };
}

TEST(BigIntSubtract, Differences) {
  for (auto const &s : differences) {
    EXPECT_EQ((BigInt(s[0]) - BigInt(s[1])).ToString(), s[2]);
  }
}
