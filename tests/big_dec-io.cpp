#include <gtest/gtest.h>
#include <string>

import numex.big_dec;
import numex.big_int;

using numex::BigDec;
using numex::BigInt;

// The pre-rename version of this file printed its results rather than asserting
// on them, so the expectations below cover the shape of the output instead of
// values nobody ever recorded.

TEST(BigDecIo, MixedBaseConstruction) {
  auto const a = BigDec(BigInt(1), BigInt("34534534"));
  EXPECT_EQ(a.ToString(), "1/34534534");

  // A value and its denominator written in base 62 reduce to 1.
  auto const b = BigDec(BigInt("-SomeNumbersAreHere::62"), BigInt("-SomeNumbersAreHere::62"));
  EXPECT_EQ(b.ToString(), "1/1");
  EXPECT_EQ(b, 1);
}

TEST(BigDecIo, BaseRoundTrip) {
  auto const a = BigDec(BigInt(1), BigInt("34534534"));
  EXPECT_EQ(BigDec(a.Base(62)), a);
  EXPECT_EQ(BigDec(a.Base(32)), a);
}

TEST(BigDecIo, PointHasRequestedPlaces) {
  auto const a = BigDec(BigInt(1), BigInt("34534534"));
  auto const point = a.Point(50);
  auto const dot = point.find('.');
  ASSERT_NE(dot, std::string::npos);
  EXPECT_EQ(point.size() - dot - 1, 50u);
}

TEST(BigDecIo, StreamsAsToString) {
  auto const a = BigDec(BigInt(3), BigInt(4));
  auto stream = std::ostringstream();
  stream << a;
  EXPECT_EQ(stream.str(), a.ToString());
}