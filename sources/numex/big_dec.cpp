module;
#include <numex/macros.hpp>

export module numex.big_dec;
import numex.big_int;
import std;

namespace numex {
  export class BigDec;
}

class numex::BigDec {
  BigInt _Numerator{};
  BigInt _Denominator{};
  auto _Simplify() -> void;

public:
  BigDec();
  explicit BigDec(std::int64_t num);
  explicit BigDec(std::string const &s);
  BigDec(BigInt const &num, BigInt const &den);

  NUMEX_NODISCARD auto GetNumerator() const -> BigInt;
  NUMEX_NODISCARD auto GetDenominator() const -> BigInt;
  NUMEX_NODISCARD auto IsNegative() const -> bool;
  NUMEX_NODISCARD auto ToString() const -> std::string;
  NUMEX_NODISCARD auto Base(std::uint64_t base) const -> std::string;
  NUMEX_NODISCARD auto Point(std::uint64_t num) const -> std::string;
  NUMEX_NODISCARD auto Point(std::uint64_t num, std::uint64_t base) const -> std::string;

  auto operator ++(int) -> BigDec;
  auto operator ++() -> BigDec&;
  auto operator --(int) -> BigDec;
  auto operator --() -> BigDec&;
  auto operator -() const -> BigDec;
  auto operator +(BigDec const &a) const -> BigDec;
  auto operator +=(BigDec const &a) -> BigDec&;
  auto operator -(BigDec const &a) const -> BigDec;
  auto operator -=(BigDec const &a) -> BigDec&;
  auto operator *(BigDec const &a) const -> BigDec;
  auto operator *=(BigDec const &a) -> BigDec&;
  auto operator /(BigDec const &a) const -> BigDec;
  auto operator /=(BigDec const &a) -> BigDec&;

  auto operator ==(BigDec const &b) const -> bool;
  auto operator <=>(BigDec const &b) const -> std::strong_ordering;
  auto operator ==(std::int64_t a) const -> bool;
  auto operator <=>(std::int64_t a) const -> std::strong_ordering;

  NUMEX_NODISCARD auto Pow(std::uint64_t exp) const -> BigDec;
  NUMEX_NODISCARD auto Gcd(BigDec const &b) const -> BigDec;
  NUMEX_NODISCARD auto Lcm(BigDec const &b) const -> BigDec;
};

export auto operator <<(std::ostream &strm, numex::BigDec const &a) -> std::ostream&;
export auto operator +(std::int64_t a, numex::BigDec const &b) -> numex::BigDec;
export auto operator -(std::int64_t a, numex::BigDec const &b) -> numex::BigDec;
export auto operator *(std::int64_t a, numex::BigDec const &b) -> numex::BigDec;
export auto operator /(std::int64_t a, numex::BigDec const &b) -> numex::BigDec;

numex::BigDec::BigDec() :
  _Numerator(BigInt(0)),
  _Denominator(BigInt(1)) {
}

numex::BigDec::BigDec(BigInt const &num, BigInt const &den) :
  _Numerator(num),
  _Denominator(den) {
  _Simplify();
}

numex::BigDec::BigDec(std::int64_t const num) :
  _Numerator(BigInt(num)),
  _Denominator(BigInt(1)) {
}

numex::BigDec::BigDec(std::string const &s) {
  auto const end = s.find('/');
  _Numerator = BigInt(s.substr(0, end));
  _Denominator = end != std::string::npos ? BigInt(s.substr(end + 1)) : BigInt(1);
  _Simplify();
}

auto numex::BigDec::_Simplify() -> void {
  if (_Denominator < 0) {
    _Denominator = -_Denominator;
    _Numerator = -_Numerator;
  }

  auto const c = _Numerator.Gcd(_Denominator);
  if (c != 1) {
    _Numerator /= c;
    _Denominator /= c;
  }
}

auto numex::BigDec::GetNumerator() const -> BigInt {
  return _Numerator;
}

auto numex::BigDec::GetDenominator() const -> BigInt {
  return _Denominator;
}

auto numex::BigDec::IsNegative() const -> bool {
  return _Numerator.IsNegative();
}

auto numex::BigDec::ToString() const -> std::string {
  return Base(10);
}

auto numex::BigDec::Base(std::uint64_t const base) const -> std::string {
  return _Numerator.Base(base) + '/' + _Denominator.Base(base);
}

auto numex::BigDec::Point(std::uint64_t const num) const -> std::string {
  return Point(num, 10);
}

auto numex::BigDec::Point(std::uint64_t const num, std::uint64_t const base) const -> std::string {
  if (base < 2 || base > static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())) {
    throw std::invalid_argument("Base must be at least 2 and fit a signed 64-bit integer!");
  }

  auto const scale = static_cast<std::int64_t>(base);
  auto a = _Numerator;
  auto t = a / _Denominator;
  a %= _Denominator;
  if (a < 0) { a = -a; }

  auto s = std::string(t == 0 && _Numerator < 0 ? "-" : "");
  s += t.Base(base);
  s = s.substr(0, s.find("::")) + '.';

  auto i = static_cast<std::uint64_t>(0);
  for (i = num; i != 0; --i) {
    a *= scale;
    t = a / _Denominator;
    a %= _Denominator;
    if (t != 0) break;
    s += BigInt::ZeroDigit(base);
  }

  auto b = BigInt();
  for (; i != 0; --i) {
    b *= scale;
    b += t;

    a *= scale;
    t = a / _Denominator;
    a %= _Denominator;
  }

  return s + b.Base(base);
}

auto operator <<(std::ostream &strm, numex::BigDec const &a) -> std::ostream& {
  return strm << a.ToString();
}

auto numex::BigDec::operator +(BigDec const &a) const -> BigDec {
  auto b = *this;
  b += a;
  return b;
}

auto numex::BigDec::operator +=(BigDec const &a) -> BigDec& {
  _Numerator *= a._Denominator;
  _Numerator += _Denominator * a._Numerator;
  _Denominator *= a._Denominator;
  _Simplify();
  return *this;
}

auto numex::BigDec::operator -(BigDec const &a) const -> BigDec {
  auto b = *this;
  b -= a;
  return b;
}

auto numex::BigDec::operator -=(BigDec const &a) -> BigDec& {
  auto b = a;
  b._Numerator = -b._Numerator;
  *this += b;
  return *this;
}

auto numex::BigDec::operator *(BigDec const &a) const -> BigDec {
  auto b = *this;
  b *= a;
  return b;
}

auto numex::BigDec::operator *=(BigDec const &a) -> BigDec& {
  _Numerator *= a._Numerator;
  _Denominator *= a._Denominator;
  _Simplify();
  return *this;
}

auto numex::BigDec::operator /(BigDec const &a) const -> BigDec {
  auto b = *this;
  b /= a;
  return b;
}

auto numex::BigDec::operator /=(BigDec const &a) -> BigDec& {
  _Numerator *= a._Denominator;
  _Denominator *= a._Numerator;
  _Simplify();
  return *this;
}

auto numex::BigDec::operator ++() -> BigDec& {
  _Numerator += _Denominator;
  return *this;
}

auto numex::BigDec::operator ++(int) -> BigDec {
  auto b = *this;
  ++*this;
  return b;
}

auto numex::BigDec::operator --() -> BigDec& {
  _Numerator -= _Denominator;
  return *this;
}

auto numex::BigDec::operator --(int) -> BigDec {
  auto b = *this;
  --*this;
  return b;
}

auto numex::BigDec::operator -() const -> BigDec {
  auto a = *this;
  a._Numerator = -a._Numerator;
  return a;
}

auto operator +(std::int64_t const a, numex::BigDec const &b) -> numex::BigDec {
  auto c = numex::BigDec(a);
  c += b;
  return c;
}

auto operator -(std::int64_t const a, numex::BigDec const &b) -> numex::BigDec {
  auto d = numex::BigDec(a);
  d -= b;
  return d;
}

auto operator *(std::int64_t const a, numex::BigDec const &b) -> numex::BigDec {
  auto c = numex::BigDec(a);
  c *= b;
  return c;
}

auto operator /(std::int64_t const a, numex::BigDec const &b) -> numex::BigDec {
  auto c = numex::BigDec(a);
  c /= b;
  return c;
}

auto numex::BigDec::operator ==(BigDec const &b) const -> bool {
  return _Numerator == b._Numerator && _Denominator == b._Denominator;
}

auto numex::BigDec::operator <=>(BigDec const &b) const -> std::strong_ordering {
  return _Numerator * b._Denominator <=> b._Numerator * _Denominator;
}

auto numex::BigDec::operator ==(std::int64_t const a) const -> bool {
  return _Denominator == 1 && _Numerator == a;
}

auto numex::BigDec::operator <=>(std::int64_t const a) const -> std::strong_ordering {
  return _Numerator <=> _Denominator * a;
}

auto numex::BigDec::Pow(std::uint64_t const exp) const -> BigDec {
  return BigDec(_Numerator.Pow(exp), _Denominator.Pow(exp));
}

auto numex::BigDec::Gcd(BigDec const &b) const -> BigDec {
  return BigDec(_Numerator.Gcd(b._Numerator), _Denominator.Lcm(b._Denominator));
}

auto numex::BigDec::Lcm(BigDec const &b) const -> BigDec {
  auto const c = *this * b / Gcd(b);
  if (c < 0) return -c;
  return c;
}
