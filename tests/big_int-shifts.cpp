#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { n, 1 << n }
  auto const shifts = std::vector<std::pair<std::uint64_t, std::string>>{
    {61, "2305843009213693952"}, {62, "4611686018427387904"}, {63, "9223372036854775808"},
    {64, "18446744073709551616"}, {65, "36893488147419103232"},
  };
}

TEST(BigIntShifts, LeftPositives) {
  for (auto const &[shift, expected] : shifts) {
    auto a = BigInt("1");
    a <<= shift;
    EXPECT_EQ(a.ToString(), expected);
  }
}

TEST(BigIntShifts, LeftNegatives) {
  for (auto const &[shift, expected] : shifts) {
    auto a = BigInt("-1");
    a <<= shift;
    EXPECT_EQ(a.ToString(), "-" + expected);
  }
}

TEST(BigIntShifts, RightPositives) {
  for (auto const &[shift, expected] : shifts) {
    auto a = BigInt("1");
    a <<= shift + 1;
    a >>= 1;
    EXPECT_EQ(a.ToString(), expected);
  }
}

TEST(BigIntShifts, RightNegatives) {
  for (auto const &[shift, expected] : shifts) {
    auto a = BigInt("-1");
    a <<= shift + 1;
    a >>= 1;
    EXPECT_EQ(a.ToString(), "-" + expected);
  }
}

TEST(BigIntShifts, LeftByTwo) {
  auto a = BigInt("5000000000000000000");
  a <<= 2;
  EXPECT_EQ(a.ToString(), "20000000000000000000");
}
