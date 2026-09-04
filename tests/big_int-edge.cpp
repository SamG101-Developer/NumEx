#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <string>

import numex.big_int;

using numex::BigInt;

namespace {
  constexpr auto int64Min = std::numeric_limits<std::int64_t>::min();
  constexpr auto int64Max = std::numeric_limits<std::int64_t>::max();
}

// Shifting by a whole limb width or more used to shift an int by 64.
TEST(BigIntEdge, ShiftAcrossLimbBoundary) {
  EXPECT_EQ((BigInt(1) << 62).ToString(), "4611686018427387904");
  EXPECT_EQ((BigInt(1) << 63).ToString(), "9223372036854775808");
  EXPECT_EQ((BigInt(1) << 64).ToString(), "18446744073709551616");
  EXPECT_EQ((BigInt(1) << 127).ToString(), "170141183460469231731687303715884105728");

  EXPECT_EQ(((BigInt(1) << 63) >> 63).ToString(), "1");
  EXPECT_EQ(((BigInt(1) << 64) >> 64).ToString(), "1");
  EXPECT_EQ(((BigInt(1) << 127) >> 127).ToString(), "1");
}

// A zero shift must not shift a mask by the full limb width.
TEST(BigIntEdge, ShiftByZero) {
  EXPECT_EQ((BigInt(12345) << 0).ToString(), "12345");
  EXPECT_EQ((BigInt(12345) >> 0).ToString(), "12345");
  EXPECT_EQ((BigInt(-12345) << 0).ToString(), "-12345");
  EXPECT_EQ((BigInt(-12345) >> 0).ToString(), "-12345");
}

// Right shift is arithmetic, so a negative value saturates at -1 rather than 0.
TEST(BigIntEdge, RightShiftPastTheEnd) {
  EXPECT_EQ((BigInt(-1) >> 100).ToString(), "-1");
  EXPECT_EQ((BigInt(-12345) >> 500).ToString(), "-1");
  EXPECT_EQ((BigInt(12345) >> 500).ToString(), "0");
}

// Negating INT64_MIN overflows, so the scalar operators must not try.
TEST(BigIntEdge, Int64Min) {
  EXPECT_EQ(BigInt(int64Min).ToString(), "-9223372036854775808");
  EXPECT_EQ((-BigInt(int64Min)).ToString(), "9223372036854775808");
  EXPECT_EQ((BigInt(3) * int64Min).ToString(), "-27670116110564327424");
  EXPECT_EQ((BigInt(int64Min) * int64Min).ToString(), "85070591730234615865843651857942052864");
  EXPECT_EQ((BigInt(0) - int64Min).ToString(), "9223372036854775808");
  EXPECT_EQ((BigInt(int64Min) - int64Min).ToString(), "0");
  EXPECT_EQ((BigInt(int64Min) + int64Min).ToString(), "-18446744073709551616");
}

TEST(BigIntEdge, Int64Max) {
  EXPECT_EQ(BigInt(int64Max).ToString(), "9223372036854775807");
  EXPECT_EQ((BigInt(int64Max) + 1).ToString(), "9223372036854775808");
  EXPECT_EQ((BigInt(int64Max) * int64Max).ToString(), "85070591730234615847396907784232501249");
}

// A modulus or exponent above INT64_MAX used to reinterpret as negative.
TEST(BigIntEdge, ModPowWithUnsignedModulus) {
  constexpr auto modulus = std::uint64_t{9223372036854775809u}; // 2^63 + 1
  EXPECT_EQ(BigInt("100000000000000000000").ModPow(1, modulus).ToString(), "7766279631452241910");
  EXPECT_EQ(BigInt(2).ModPow(10, modulus).ToString(), "1024");
  EXPECT_EQ(BigInt(2).ModPow(10, 1000).ToString(), "24");
  EXPECT_EQ(BigInt(2).ModPow(10, 1).ToString(), "0");
}

TEST(BigIntEdge, RejectsMalformedInput) {
  EXPECT_THROW((void)BigInt(""), std::invalid_argument);
  EXPECT_THROW((void)BigInt("-"), std::invalid_argument);
  EXPECT_THROW((void)BigInt("12x45"), std::invalid_argument);
}

// Base 1 never reduces the value, so rendering it would spin forever.
TEST(BigIntEdge, RejectsDegenerateBase) {
  auto const a = BigInt(255);
  EXPECT_THROW((void)a.Base(0), std::invalid_argument);
  EXPECT_THROW((void)a.Base(1), std::invalid_argument);
  EXPECT_EQ(a.Base(16), "ff::16");
}

TEST(BigIntEdge, ZeroBehaviour) {
  auto const zero = BigInt();
  EXPECT_EQ(zero.ToString(), "0");
  EXPECT_TRUE(zero == 0);
  EXPECT_EQ((zero - zero).ToString(), "0");
  EXPECT_EQ((zero * BigInt("123456789012345678901234567890")).ToString(), "0");
  EXPECT_EQ(zero.Gcd(BigInt(12)).ToString(), "12");
  EXPECT_EQ(BigInt(12).Gcd(zero).ToString(), "12");
  EXPECT_THROW((void)(BigInt(1) / zero), std::invalid_argument);
  EXPECT_THROW((void)(BigInt(1) % zero), std::invalid_argument);
}

// Round-tripping across the limb boundary catches sign-extension mistakes.
TEST(BigIntEdge, NegativeRoundTrip) {
  for (auto const *text : {"-1", "-9223372036854775808", "-18446744073709551616",
                           "-170141183460469231731687303715884105728"}) {
    EXPECT_EQ(BigInt(text).ToString(), text);
    EXPECT_EQ((-(-BigInt(text))).ToString(), text);
  }
}