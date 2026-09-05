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
  explicit BigDec(BigInt const &num, BigInt const &den = {});

  NUMEX_NODISCARD auto GetNumerator() const -> BigInt;
  NUMEX_NODISCARD auto GetDenominator() const -> BigInt;
  NUMEX_NODISCARD auto IsNegative() const -> bool;
  NUMEX_NODISCARD auto ToString() const -> std::string;
  NUMEX_NODISCARD auto Decimal(std::uint64_t max_places = 64) const -> std::string;
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

  NUMEX_NODISCARD auto Abs() const -> BigDec;
  NUMEX_NODISCARD auto Max(BigDec const &b) const -> BigDec;
  NUMEX_NODISCARD auto Min(BigDec const &b) const -> BigDec;

  NUMEX_NODISCARD auto Floor() const -> BigInt;
  NUMEX_NODISCARD auto Ceil() const -> BigInt;
  NUMEX_NODISCARD auto Trunc() const -> BigInt;
  NUMEX_NODISCARD auto Round() const -> BigInt;
  NUMEX_NODISCARD auto Fmod(BigDec const &b) const -> BigDec;

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
  // "n/d" is the explicit rational form; either side is whatever BigInt spells.
  if (auto const bar = s.find('/'); bar != std::string::npos) {
    _Numerator = BigInt(s.substr(0, bar));
    _Denominator = BigInt(s.substr(bar + 1));
    _Simplify();
    return;
  }

  // A "digits::base" suffix or an 0b/0o/0x prefix means a whole number in another base, which BigInt already reads.
  auto const body = std::string_view(s).substr(!s.empty() && (s.front() == '-' || s.front() == '+') ? 1 : 0);
  auto const prefixed = body.size() >= 2 && body.front() == '0' && std::string_view("bBoOxX").contains(body[1]);
  if (prefixed || s.find("::") != std::string::npos) {
    _Numerator = BigInt(s);
    _Denominator = BigInt(1);
    _Simplify();
    return;
  }

  // Otherwise a decimal, written with an optional fraction and an optional power-of-ten exponent.
  auto mantissa = std::string(!s.empty() && s.front() == '-' ? "-" : "");
  auto places = std::int64_t{0};
  auto exponent = std::int64_t{0};
  auto point = false;
  auto digits = false;

  auto i = static_cast<std::size_t>(body.data() - s.data());
  for (; i < s.size(); ++i) {
    auto const c = s[i];
    if (c == 'e' || c == 'E') { break; }
    if (c == '.') {
      if (point) { throw std::invalid_argument("Unexpected symbol! - '.'"); }
      point = true;
      continue;
    }
    if (c < '0' || c > '9') {
      auto err = std::string("Unexpected symbol! - '");
      err.push_back(c);
      err.push_back('\'');
      throw std::invalid_argument(err);
    }
    mantissa.push_back(c);
    digits = true;
    if (point) { ++places; }
  }

  if (!digits) {
    throw std::invalid_argument("Empty number!");
  }

  if (i < s.size()) {
    auto const text = std::string_view(s).substr(i + 1);
    auto const first = text.data() + (!text.empty() && text.front() == '+' ? 1 : 0);
    auto const last = text.data() + text.size();
    if (auto const [ptr, ec] = std::from_chars(first, last, exponent); ec != std::errc{} || ptr != last) {
      throw std::invalid_argument("Invalid exponent! - '" + std::string(text) + "'");
    }
  }

  _Numerator = BigInt(mantissa);
  _Denominator = BigInt(1);
  if (auto const shift = exponent - places; shift > 0) {
    _Numerator *= BigInt(10).Pow(static_cast<std::uint64_t>(shift));
  }
  else if (shift < 0) {
    _Denominator = BigInt(10).Pow(static_cast<std::uint64_t>(-shift));
  }
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

auto numex::BigDec::Decimal(std::uint64_t const max_places) const -> std::string {
  // The sign is carried separately so that a magnitude below one still prints as "-0.5".
  auto const neg = IsNegative();
  auto rmd = neg ? -_Numerator : _Numerator;
  auto const whole = rmd / _Denominator;
  rmd %= _Denominator;

  auto s = std::string(neg ? "-" : "") + whole.ToString();

  // A fraction that terminates within the budget is exact; one that does not is cut short here.
  auto frac = std::string();
  for (auto i = static_cast<std::uint64_t>(0); i < max_places && rmd != 0; ++i) {
    rmd *= 10;
    frac += (rmd / _Denominator).ToString();
    rmd %= _Denominator;
  }

  while (!frac.empty() && frac.back() == '0') { frac.pop_back(); }
  return frac.empty() ? s : s + '.' + frac;
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

auto numex::BigDec::Abs() const -> BigDec {
  return IsNegative() ? -*this : *this;
}

auto numex::BigDec::Max(BigDec const &b) const -> BigDec {
  return *this < b ? b : *this;
}

auto numex::BigDec::Min(BigDec const &b) const -> BigDec {
  return b < *this ? b : *this;
}

auto numex::BigDec::Trunc() const -> BigInt {
  return _Numerator / _Denominator;
}

auto numex::BigDec::Floor() const -> BigInt {
  auto quot = Trunc();
  if (!IsNegative() || quot * _Denominator == _Numerator) return quot;
  return quot - BigInt(1);
}

auto numex::BigDec::Ceil() const -> BigInt {
  auto quot = Trunc();
  if (IsNegative() || quot * _Denominator == _Numerator) return quot;
  return quot + BigInt(1);
}

auto numex::BigDec::Round() const -> BigInt {
  auto quot = Trunc();
  auto const rmd = (_Numerator - quot * _Denominator).Abs();
  if (rmd * BigInt(2) < _Denominator) return quot;
  return IsNegative() ? quot - BigInt(1) : quot + BigInt(1);
}

auto numex::BigDec::Fmod(BigDec const &b) const -> BigDec {
  if (b == 0) {
    throw std::invalid_argument("Division by zero!");
  }

  auto const quot = (*this / b).Trunc();
  return *this - b * BigDec(quot, BigInt(1));
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
