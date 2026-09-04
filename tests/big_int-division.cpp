#include <gtest/gtest.h>
#include <string>
#include <vector>

import numex.big_int;

using numex::BigInt;

namespace {
  // { dividend, divisor, quotient, remainder }
  auto const divisions = std::vector<std::vector<std::string>>{
    {"563456345634562456245643563456345634563657456745676345634563456345661", "245635675674678567856785678545674567", "2293870155818927461038824163537040", "194671830340138360905494231965883981"},
    {"83453834556575478678469789567895678546534563455634563456345624562456345634563456345661", "2305843009213693952", "36192331491393999030911367620299278682605219448051027508900256529311", "361706202184918589"},
    {"345345997282345246457356724523465356745677423452345245656736562452452346456245", "4611686018427387904", "74884976102538365282049165625998607397784258852309259060588","1168204170632128693"},
    {"9223372036854775810", "9223372036854775808", "1", "2"},
    {"64435345345345223423", "18446744073709551616", "3", "9095113124216568575"},
    {"653453453453453453443333333333333333333333333333333333333333333333333", "36893488147419103232", "17711891346309742104832430041142880365138504809389", "18880027887859488085"},
    {"64435345345", "18446744073709551616", "0", "64435345345"},
    {"0", "18446744073709551616", "0", "0"},
    //{"0", "0", "0", "0"},
  };

  // A zero result carries no sign, so it stays "0" rather than becoming "-0".
  auto negated(std::string const &value) -> std::string {
    return value == "0" ? value : "-" + value;
  }
}

TEST(BigIntDivision, Positives) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt(s[0]) / BigInt(s[1])).ToString(), s[2]);
  }
}

TEST(BigIntDivision, NegativeDividend) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt("-" + s[0]) / BigInt(s[1])).ToString(), negated(s[2]));
  }
}

TEST(BigIntDivision, NegativeDivisor) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt(s[0]) / BigInt("-" + s[1])).ToString(), negated(s[2]));
  }
}

TEST(BigIntDivision, RemainderPositives) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt(s[0]) % BigInt(s[1])).ToString(), s[3]);
  }
}

TEST(BigIntDivision, RemainderNegativeDividend) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt("-" + s[0]) % BigInt(s[1])).ToString(), negated(s[3]));
  }
}

TEST(BigIntDivision, RemainderNegativeDivisor) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt(s[0]) % BigInt("-" + s[1])).ToString(), s[3]);
  }
}

TEST(BigIntDivision, RemainderBothNegative) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt("-" + s[0]) % BigInt("-" + s[1])).ToString(), negated(s[3]));
  }
}

TEST(BigIntDivision, BothNegative) {
  for (auto const &s : divisions) {
    EXPECT_EQ((BigInt("-" + s[0]) / BigInt("-" + s[1])).ToString(), s[2]);
  }
}

TEST(BigIntDivision, DivisionIdentity) {
  for (auto const &s : divisions) {
    for (auto const &an : {s[0], negated(s[0])}) {
      for (auto const &bn : {s[1], negated(s[1])}) {
        auto const a = BigInt(an);
        auto const b = BigInt(bn);
        EXPECT_EQ((a / b) * b + a % b, a) << an << ", " << bn;
      }
    }
  }
}
