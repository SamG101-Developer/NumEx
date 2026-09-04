#include <gtest/gtest.h>
#include <string>

import numex.big_int;

using numex::BigInt;

// C++ parses these itself, so they arrive as a plain std::int64_t and are capped
// at 64 bits. The string forms below are the arbitrary-precision route.
TEST(BigIntLiterals, BuiltInIntegerLiterals) {
  EXPECT_EQ(BigInt(0xff).ToString(), "255");
  EXPECT_EQ(BigInt(0b1010).ToString(), "10");
  EXPECT_EQ(BigInt(0777).ToString(), "511");
  EXPECT_EQ(BigInt(-0xff).ToString(), "-255");
}

TEST(BigIntLiterals, PrefixedStrings) {
  EXPECT_EQ(BigInt("0xff").ToString(), "255");
  EXPECT_EQ(BigInt("0b1010").ToString(), "10");
  EXPECT_EQ(BigInt("0o777").ToString(), "511");
  EXPECT_EQ(BigInt("0xdeadbeef").ToString(), "3735928559");

  // The prefix letter is accepted in either case; the digits still follow the
  // alphabet, which is lower case.
  EXPECT_EQ(BigInt("0Xff").ToString(), "255");
  EXPECT_EQ(BigInt("0B1010").ToString(), "10");
  EXPECT_EQ(BigInt("0O777").ToString(), "511");
}

TEST(BigIntLiterals, PrefixedStringsAreSigned) {
  EXPECT_EQ(BigInt("-0xff").ToString(), "-255");
  EXPECT_EQ(BigInt("-0b1010").ToString(), "-10");
  EXPECT_EQ(BigInt("-0o777").ToString(), "-511");
}

// Past 64 bits only the string forms work.
TEST(BigIntLiterals, PrefixedStringsBeyond64Bits) {
  EXPECT_EQ(BigInt("0x10000000000000000").ToString(), "18446744073709551616");
  EXPECT_EQ(BigInt("0b1" + std::string(64, '0')).ToString(), "18446744073709551616");
  EXPECT_EQ(BigInt("0x18ee90ff6c373e0ee4e3f0ad2").ToString(), "123456789012345678901234567890");
}

// A prefixed string and the equivalent "::base" suffix must agree.
TEST(BigIntLiterals, AgreesWithBaseSuffix) {
  EXPECT_EQ(BigInt("0xff"), BigInt("ff::16"));
  EXPECT_EQ(BigInt("0b1010"), BigInt("1010::2"));
  EXPECT_EQ(BigInt("0o777"), BigInt("777::8"));
  EXPECT_EQ(BigInt("-0xff"), BigInt("-ff::16"));
}

TEST(BigIntLiterals, RejectsMalformedPrefixes) {
  EXPECT_THROW((void)BigInt("0x"), std::invalid_argument);      // no digits
  EXPECT_THROW((void)BigInt("0b"), std::invalid_argument);
  EXPECT_THROW((void)BigInt("0o"), std::invalid_argument);
  EXPECT_THROW((void)BigInt("0b2"), std::invalid_argument);     // not a binary digit
  EXPECT_THROW((void)BigInt("0o8"), std::invalid_argument);     // not an octal digit
  EXPECT_THROW((void)BigInt("0xg"), std::invalid_argument);     // not a hex digit
  EXPECT_THROW((void)BigInt("0xFF"), std::invalid_argument);    // alphabet is lower case
}

// A bare leading zero is still decimal, not octal, so nothing changes meaning.
TEST(BigIntLiterals, BareLeadingZeroStaysDecimal) {
  EXPECT_EQ(BigInt("0").ToString(), "0");
  EXPECT_EQ(BigInt("00").ToString(), "0");
  EXPECT_EQ(BigInt("0777").ToString(), "777");
}

// Oct() used to emit a bare leading '0', so this round trip silently produced
// 377 instead of 255. The 0o prefix removes the ambiguity.
TEST(BigIntLiterals, PrintedFormsRoundTrip) {
  for (auto const *text : {"0", "1", "255", "18446744073709551616",
                           "123456789012345678901234567890"}) {
    auto const a = BigInt(text);
    EXPECT_EQ(BigInt(a.Hex()), a) << "hex of " << text << " was " << a.Hex();
    EXPECT_EQ(BigInt(a.Bin()), a) << "bin of " << text;
    EXPECT_EQ(BigInt(a.Oct()), a) << "oct of " << text << " was " << a.Oct();
  }
}

TEST(BigIntLiterals, PrintedFormsCarryTheirPrefix) {
  auto const a = BigInt(255);
  EXPECT_TRUE(a.Hex().starts_with("0x"));
  EXPECT_TRUE(a.Bin().starts_with("0b"));
  EXPECT_TRUE(a.Oct().starts_with("0o"));
  EXPECT_TRUE(a.Hex().ends_with("ff"));
  EXPECT_TRUE(a.Bin().ends_with("11111111"));
  EXPECT_TRUE(a.Oct().ends_with("377"));
}

// Bin/Hex/Oct are two's complement bit views: zero padded to the storage width
// and unsigned, unlike the sign-and-magnitude Base(). So a negative value does
// not round trip through them -- use Base(n) for that.
TEST(BigIntLiterals, NegativesPrintAsTwosComplement) {
  auto const a = BigInt(-255);
  EXPECT_EQ(a.Hex(), "0xffffffffffffff01");
  EXPECT_EQ(a.Base(16), "-ff::16");
  EXPECT_EQ(BigInt(a.Base(16)), a);

  // Reading the bit pattern back gives the unsigned value it denotes.
  EXPECT_EQ(BigInt(a.Hex()).ToString(), "18446744073709551361");
}