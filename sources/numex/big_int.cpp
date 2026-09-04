module;
#include <numex/macros.hpp>

export module numex.big_int;
import std;

namespace numex {
  export class BigInt;
}

class numex::BigInt {
  static constexpr auto _LimbBits = static_cast<std::uint64_t>(std::numeric_limits<std::uint64_t>::digits);

  std::vector<std::uint64_t> _Number;
  static std::string const _Alphabet;

  auto AddUintWithCarry(std::uint64_t &operand1res, std::uint64_t operand2, bool &carry) const -> void;
  auto Mult(std::uint64_t &operand1ResHigh, std::uint64_t &operand2ResLow) const -> void;
  template <typename Op>
  auto _BitOp(BigInt const &a, Op op) -> BigInt&;
  template <typename Op>
  auto _BitOp(std::int64_t a, Op op) -> BigInt&;
  auto _EraseLeadingSign() -> void;
  auto _ExtendNumberBySizeOf(BigInt &extNumber, BigInt const &a) -> void;
  auto _Div(std::uint64_t const &dividend, std::uint64_t const &divisor, std::uint64_t &prevRmd) const -> std::uint64_t;
  auto _Div(BigInt &rmdDividend, BigInt &resQuot, BigInt const &divisor) const -> void;
  auto _SetDecimal(std::string const &s) -> void;
  auto _SetNumber(std::string const &num, int base) -> void;
  NUMEX_NODISCARD auto _Base2(std::uint64_t base) const -> std::string;
  auto _URShift(std::uint64_t shift) -> BigInt&;
  auto _AddUintAt(std::uint64_t index, std::uint64_t operand) -> void;
  static auto _OddFact(std::uint64_t a, std::uint64_t begin) -> BigInt;
  static auto _FromUnsigned(std::uint64_t value) -> BigInt;
  NUMEX_NODISCARD auto _CountTrailingZeros() const -> std::uint64_t;

public:
  BigInt();
  explicit BigInt(std::int64_t num);
  explicit BigInt(std::string const &text);

  NUMEX_NODISCARD auto IsNegative() const -> bool;

  NUMEX_NODISCARD auto Bin() const -> std::string;
  NUMEX_NODISCARD auto Hex() const -> std::string;
  NUMEX_NODISCARD auto Oct() const -> std::string;
  NUMEX_NODISCARD auto ToString() const -> std::string;
  NUMEX_NODISCARD auto Base(std::uint64_t base) const -> std::string;
  NUMEX_NODISCARD static auto ZeroDigit(std::uint64_t base) -> std::string;

  auto operator &(BigInt const &a) const -> BigInt;
  auto operator &=(BigInt const &a) -> BigInt&;
  auto operator |(BigInt const &a) const -> BigInt;
  auto operator |=(BigInt const &a) -> BigInt&;
  auto operator ^(BigInt const &a) const -> BigInt;
  auto operator ^=(BigInt const &a) -> BigInt&;

  auto operator &(std::int64_t a) const -> BigInt;
  auto operator &=(std::int64_t a) -> BigInt&;
  auto operator |(std::int64_t a) const -> BigInt;
  auto operator |=(std::int64_t a) -> BigInt&;
  auto operator ^(std::int64_t a) const -> BigInt;
  auto operator ^=(std::int64_t a) -> BigInt&;

  auto operator ~() const -> BigInt;

  auto operator ++(int) -> BigInt;
  auto operator ++() -> BigInt&;
  auto operator --(int) -> BigInt;
  auto operator --() -> BigInt&;
  auto operator -() const -> BigInt;

  auto operator +(BigInt const &a) const -> BigInt;
  auto operator +=(BigInt const &a) -> BigInt&;
  auto operator -(BigInt const &a) const -> BigInt;
  auto operator -=(BigInt const &a) -> BigInt&;
  auto operator *(BigInt const &a) const -> BigInt;
  auto operator *=(BigInt const &a) -> BigInt&;
  auto operator /(BigInt const &a) const -> BigInt;
  auto operator /=(BigInt const &a) -> BigInt&;
  auto operator %(BigInt const &a) const -> BigInt;
  auto operator %=(BigInt const &a) -> BigInt&;

  auto operator +(std::int64_t a) const -> BigInt;
  auto operator +=(std::int64_t a) -> BigInt&;
  auto operator -(std::int64_t a) const -> BigInt;
  auto operator -=(std::int64_t a) -> BigInt&;
  auto operator *(std::int64_t a) const -> BigInt;
  auto operator *=(std::int64_t a) -> BigInt&;
  auto operator /(std::int64_t a) const -> BigInt;
  auto operator /=(std::int64_t a) -> BigInt&;
  auto operator %(std::int64_t a) const -> BigInt;
  auto operator %=(std::int64_t a) -> BigInt&;

  auto operator <<(std::uint64_t shift) const -> BigInt;
  auto operator <<=(std::uint64_t shift) -> BigInt&;
  auto operator >>(std::uint64_t shift) const -> BigInt;
  auto operator >>=(std::uint64_t shift) -> BigInt&;

  auto operator ==(BigInt const &b) const -> bool;
  auto operator <=>(BigInt const &b) const -> std::strong_ordering;

  auto operator ==(std::int64_t a) const -> bool;
  auto operator <=>(std::int64_t a) const -> std::strong_ordering;

  NUMEX_NODISCARD auto Abs() const -> BigInt;
  NUMEX_NODISCARD auto Max(BigInt const &b) const -> BigInt;
  NUMEX_NODISCARD auto Min(BigInt const &b) const -> BigInt;
  NUMEX_NODISCARD auto Pow(std::uint64_t exp) const -> BigInt;
  NUMEX_NODISCARD auto ModPow(std::uint64_t exp, std::uint64_t mod) const -> BigInt;
  NUMEX_NODISCARD auto Gcd(BigInt const &b) const -> BigInt;
  NUMEX_NODISCARD auto Lcm(BigInt const &b) const -> BigInt;
  static auto Fact(std::uint64_t a) -> BigInt;
  static auto Fib(std::uint64_t a) -> BigInt;
};

export auto operator <<(std::ostream &strm, numex::BigInt const &a) -> std::ostream&;
export auto operator >>(std::istream &strm, numex::BigInt &a) -> std::istream&;
export auto operator +(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator -(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator *(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator /(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator %(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator &(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator |(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;
export auto operator ^(std::int64_t a, numex::BigInt const &b) -> numex::BigInt;

namespace {
  // The radix marked by an 0b / 0o / 0x prefix, matching what Bin(), Oct() and
  // Hex() emit; 0 for anything that is not a prefix.
  auto prefixedBase(char const marker) -> int {
    switch (marker) {
      case 'b':
      case 'B': return 2;
      case 'o':
      case 'O': return 8;
      case 'x':
      case 'X': return 16;
      default: return 0;
    }
  }
}

std::string const numex::BigInt::_Alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

numex::BigInt::BigInt() {
  _Number.push_back(0);
}

numex::BigInt::BigInt(std::string const &text) : BigInt() {
  // An explicit "digits::base" suffix wins over everything else.
  if (auto const suffix = text.rfind("::"); suffix != std::string::npos) {
    auto base = 0;
    try {
      base = std::stoi(text.substr(suffix + 2));
    }
    catch (...) {
      auto const err = std::string("Invalid base! The base should be decimal and not too big.");
      throw std::invalid_argument(err);
    }
    _SetNumber(text.substr(0, suffix), base);
    return;
  }

  // Otherwise an 0b / 0o / 0x prefix, which may follow a sign.
  auto const negative = !text.empty() && text.front() == '-';
  auto const digits = std::string_view(text).substr(negative ? 1 : 0);
  if (digits.size() >= 2 && digits.front() == '0') {
    if (auto const base = prefixedBase(digits[1]); base != 0) {
      auto body = std::string(negative ? "-" : "");
      body += digits.substr(2);
      _SetNumber(body, base);
      return;
    }
  }

  _SetDecimal(text);
}

auto numex::BigInt::_SetNumber(std::string const &num, int const base) -> void {
  if (base < 2) {
    throw std::invalid_argument("Base must be at least 2!");
  }

  auto it = num.begin();
  auto const a = _Alphabet.substr(0, std::min<std::size_t>(static_cast<std::size_t>(base), _Alphabet.size()));
  auto const neg = it != num.end() && *it == '-';
  if (neg) ++it;
  if (it == num.end()) {
    throw std::invalid_argument("Empty number!");
  }

  if (base <= static_cast<int>(_Alphabet.size())) {
    for (; it != num.end(); ++it) {
      *this *= base;
      auto const i = a.find(*it);
      if (i == std::string::npos) {
        auto err = std::string("Unexpected symbol! - '");
        err.push_back(*it);
        err.push_back('\'');
        throw std::invalid_argument(err);
      }
      *this += static_cast<std::int64_t>(i);
    }
  }
  else {
    auto prev = static_cast<std::string::size_type>(0);
    while (true) {
      const auto n = num.find(':', prev);
      auto dec = 0;
      try {
        if (n != std::string::npos) {
          dec = std::stoi(num.substr(prev, n - prev));
        }
        else {
          dec = std::stoi(num.substr(prev));
          *this *= base;
          *this += dec;
          break;
        }
      }
      catch (...) {
        auto const err = std::string("Unexpected symbol in string!");
        throw std::invalid_argument(err);
      }

      *this *= base;
      *this += dec;
      prev = n + 1;
    }
  }

  if (neg) {
    *this = -(*this);
  }

  _EraseLeadingSign();
}

numex::BigInt::BigInt(std::int64_t const num) {
  _Number.push_back(static_cast<std::uint64_t>(num));
}

auto numex::BigInt::_FromUnsigned(std::uint64_t const value) -> BigInt {
  auto result = BigInt();
  result._Number[0] = value;
  if ((value >> (_LimbBits - 1)) != 0) {
    result._Number.push_back(0);
  }
  return result;
}

auto numex::BigInt::_SetDecimal(std::string const &s) -> void {
  auto it = s.begin();

  auto const neg = it != s.end() && *it == '-';
  if (neg) ++it;
  if (it == s.end()) {
    throw std::invalid_argument("Empty number!");
  }

  for (; it != s.end(); ++it) {
    *this *= 10;
    const auto i = static_cast<std::int64_t>(*it - '0');
    if (i > 9) {
      auto err = std::string("Unexpected symbol! - ");
      err.push_back(*it);
      throw std::invalid_argument(err);
    }
    *this += i;
  }

  if (neg) {
    *this = -*this;
  }

  _EraseLeadingSign();
}

auto numex::BigInt::_EraseLeadingSign() -> void {
  auto const neg = IsNegative();
  auto const comp = neg ? ~std::uint64_t{0} : std::uint64_t{0};

  for (auto i = _Number.size() - 1; i != 0; i--) {
    if (_Number[i] != comp) break;
    auto const sign = (_Number[i - 1] >> (_LimbBits - 1)) != 0;
    if (neg == sign) _Number.erase(_Number.end() - 1);
  }
}

auto numex::BigInt::_ExtendNumberBySizeOf(BigInt &extNumber, BigInt const &a) -> void {
  auto const fill = extNumber.IsNegative() ? ~std::uint64_t{0} : std::uint64_t{0};
  if (a._Number.size() > extNumber._Number.size()) {
    extNumber._Number.resize(a._Number.size(), fill);
  }
}

auto numex::BigInt::IsNegative() const -> bool {
  return (_Number.back() >> (_LimbBits - 1)) != 0;
}

auto numex::BigInt::Bin() const -> std::string {
  return "0b" + _Base2(1);
}

auto numex::BigInt::_Base2(std::uint64_t const base) const -> std::string {
  auto const mask = (std::uint64_t{1} << base) - 1;
  auto s = std::string("");

  auto a = *this;
  auto j = a._Number.size() * _LimbBits;
  auto const limit = j / base;
  auto const rmd = j % base;
  j = 0;

  for (auto i = static_cast<std::uint64_t>(0); i < limit; i++) {
    j = a._Number[0] & mask;
    s.push_back(_Alphabet[j]);
    a._URShift(base);
  }

  if (rmd) {
    j = a._Number[0] & mask;
    s.push_back(_Alphabet[j]);
  }

  if (s.empty()) return "0";
  std::ranges::reverse(s);
  return s;
}

auto numex::BigInt::ToString() const -> std::string {
  return Base(10);
}

auto numex::BigInt::Hex() const -> std::string {
  return "0x" + _Base2(4);
}

auto numex::BigInt::Oct() const -> std::string {
  return "0o" + _Base2(3);
}

auto numex::BigInt::ZeroDigit(std::uint64_t const base) -> std::string {
  auto digit = std::string(1, _Alphabet.front());
  if (base > _Alphabet.size()) {
    digit += ':';
  }
  return digit;
}

auto numex::BigInt::Base(std::uint64_t const base) const -> std::string {
  if (base < 2) {
    throw std::invalid_argument("Base must be at least 2!");
  }

  auto const isBaseBig = (base > _Alphabet.size());

  auto temp = *this;
  auto const neg = IsNegative();
  if (neg) {
    temp = -temp;
  }

  auto current = temp._Number;
  auto s = std::string("");

  while (current[0] || (current.size() > 1)) {
    auto res = std::vector<std::uint64_t>();
    auto notFirst = false;
    auto rmd = static_cast<std::uint64_t>(0);

    for (auto const limb : current | std::views::reverse) {
      auto const quot = _Div(limb, base, rmd);
      if (quot) {
        notFirst = true;
      }
      if (notFirst) {
        res.push_back(quot);
      }
    }

    if (res.empty()) res.push_back(0);

    if (isBaseBig) {
      auto digits = rmd;
      do {
        rmd = digits % 10;
        digits = digits / 10;
        s.push_back(_Alphabet[rmd]);
      }
      while (digits);
      s.push_back(':');
    }
    else {
      s.push_back(_Alphabet[rmd]);
    }

    std::ranges::reverse(res);
    current = res;
  }

  if (s.empty()) {
    s = "0";
    if (base == 10) return s;
    return s + "::" + std::to_string(base);
  }

  if (isBaseBig) s.pop_back();
  if (neg) s += '-';

  std::ranges::reverse(s);

  if (base == 10) return s;
  return s + "::" + std::to_string(base);
}

auto operator <<(std::ostream &strm, numex::BigInt const &a) -> std::ostream& {
  return strm << a.ToString();
}

auto operator >>(std::istream &strm, numex::BigInt &a) -> std::istream& {
  auto s = std::string();
  strm >> s;
  a = numex::BigInt(s);
  return strm;
}

template <typename Op>
auto numex::BigInt::_BitOp(BigInt const &a, Op op) -> BigInt& {
  auto aa = a;
  _ExtendNumberBySizeOf(*this, aa);
  _ExtendNumberBySizeOf(aa, *this);

  for (auto const &[limb, other] : std::views::zip(_Number, aa._Number)) {
    limb = op(limb, other);
  }

  return *this;
}

template <typename Op>
auto numex::BigInt::_BitOp(std::int64_t const a, Op op) -> BigInt& {
  _Number[0] = op(_Number[0], static_cast<std::uint64_t>(a));

  // Sign-extend the scalar across the remaining limbs.
  auto const fill = a < 0 ? ~std::uint64_t{0} : std::uint64_t{0};
  for (auto &limb : _Number | std::views::drop(1)) {
    limb = op(limb, fill);
  }

  return *this;
}

auto numex::BigInt::operator |(BigInt const &a) const -> BigInt {
  auto b = *this;
  b |= a;
  return b;
}

auto numex::BigInt::operator |(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b |= a;
  return b;
}

auto numex::BigInt::operator |=(BigInt const &a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs | rhs; });
}

auto numex::BigInt::operator |=(std::int64_t const a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs | rhs; });
}

auto numex::BigInt::operator &(BigInt const &a) const -> BigInt {
  auto b = *this;
  b &= a;
  return b;
}

auto numex::BigInt::operator &(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b &= a;
  return b;
}

auto numex::BigInt::operator &=(BigInt const &a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs & rhs; });
}

auto numex::BigInt::operator &=(std::int64_t const a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs & rhs; });
}

auto numex::BigInt::operator ^(BigInt const &a) const -> BigInt {
  auto b = *this;
  b ^= a;
  return b;
}

auto numex::BigInt::operator ^(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b ^= a;
  return b;
}

auto numex::BigInt::operator ^=(BigInt const &a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs ^ rhs; });
}

auto numex::BigInt::operator ^=(std::int64_t const a) -> BigInt& {
  return _BitOp(a, [](auto lhs, auto rhs) { return lhs ^ rhs; });
}

auto numex::BigInt::operator ~() const -> BigInt {
  auto a = *this;
  for (auto &item : a._Number) {
    item = ~item;
  }
  return a;
}

auto operator &(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return b & a;
}

auto operator |(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return b | a;
}

auto operator ^(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return b ^ a;
}

auto numex::BigInt::operator +(BigInt const &a) const -> BigInt {
  auto b = *this;
  b += a;
  return b;
}

auto numex::BigInt::operator +(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b += a;
  return b;
}

auto numex::BigInt::operator +=(BigInt const &a) -> BigInt& {
  // A one-limb value is exactly its limb read as signed, so this is a
  // reinterpretation rather than a narrowing conversion.
  if (a._Number.size() == 1) return *this += static_cast<std::int64_t>(a._Number[0]);

  auto aa = a;
  _ExtendNumberBySizeOf(*this, aa);
  _ExtendNumberBySizeOf(aa, *this);

  auto const &bin = aa._Number;

  auto carry = false;

  auto const neg = IsNegative();
  auto const negA = aa.IsNegative();

  for (auto const &[limb, other] : std::views::zip(_Number, bin)) {
    AddUintWithCarry(limb, other, carry);
  }

  if ((neg == negA) && neg != IsNegative()) {
    _Number.push_back(neg ? ~std::uint64_t{0} : std::uint64_t{0});
  }

  _EraseLeadingSign();
  return *this;
}

auto numex::BigInt::operator +=(std::int64_t const a) -> BigInt& {
  auto const neg = IsNegative();
  auto const negA = a < 0;
  auto carry = false;
  AddUintWithCarry(_Number[0], static_cast<std::uint64_t>(a), carry);

  // Sign-extend the scalar into the upper limbs; a positive one only has to
  // travel as far as the carry does.
  if (negA) {
    for (auto &limb : _Number | std::views::drop(1)) {
      AddUintWithCarry(limb, ~std::uint64_t{0}, carry);
    }
  }
  else {
    for (auto &limb : _Number | std::views::drop(1)) {
      if (!carry) break;
      AddUintWithCarry(limb, std::uint64_t{0}, carry);
    }
  }

  if (neg == negA && neg != IsNegative()) {
    _Number.push_back(neg ? ~std::uint64_t{0} : std::uint64_t{0});
  }

  _EraseLeadingSign();
  return *this;
}

auto numex::BigInt::operator *(BigInt const &a) const -> BigInt {
  auto b = *this;
  b *= a;
  return b;
}

auto numex::BigInt::operator *(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b *= a;
  return b;
}

auto numex::BigInt::operator *=(std::int64_t const a) -> BigInt& {
  if (a == 1) return *this;

  auto const neg = (a < 0) != IsNegative();
  // Negating INT64_MIN overflows, so take the magnitude in unsigned space.
  auto const magnitude = a < 0 ? ~static_cast<std::uint64_t>(a) + 1 : static_cast<std::uint64_t>(a);

  if (IsNegative()) {
    *this = -*this;
  }

  auto bigCarry = std::uint64_t{0};
  auto carry = false;
  for (auto &i : _Number) {
    auto opH = magnitude;
    Mult(opH, i);
    AddUintWithCarry(i, bigCarry, carry);
    bigCarry = opH;
  }

  if (bigCarry || carry) {
    if (bigCarry != ~std::uint64_t{0}) {
      _Number.push_back(bigCarry + static_cast<std::uint64_t>(carry));
    }
    else {
      _Number.push_back(0);
      _Number.push_back(1);
    }
  }

  if (IsNegative()) {
    _Number.push_back(0);
  }

  _EraseLeadingSign();

  if (neg) {
    *this = -*this;
  }

  return *this;
}

auto numex::BigInt::operator *=(BigInt const &a) -> BigInt& {
  if (a._Number.size() == 1) return *this *= static_cast<std::int64_t>(a._Number[0]);

  auto aa = a;

  auto const neg = (a.IsNegative() != IsNegative());

  if (IsNegative()) {
    *this = -(*this);
  }

  if (aa.IsNegative()) {
    aa = -aa;
  }

  auto const &bin = aa._Number;

  auto c = BigInt();
  auto const m = bin.size() * _Number.size();
  for (auto i = m; i != 0; --i) {
    c._Number.push_back(0);
  }

  for (auto j = bin.size(); j-- > 0;) {
    for (auto i = _Number.size(); i-- > 0;) {
      auto opH = _Number[i];
      auto opL = bin[j];
      Mult(opH, opL);
      c._AddUintAt(i + j, opL);
      c._AddUintAt(i + j + 1, opH);
    }
  }

  c._EraseLeadingSign();

  if (neg) {
    c = -c;
  }

  this->_Number = c._Number;
  return *this;
}

auto numex::BigInt::Mult(std::uint64_t &operand1ResHigh, std::uint64_t &operand2ResLow) const -> void {
#if defined(__SIZEOF_INT128__)
  // A single widening multiply where the portable path below needs four 32-bit
  // partial products and their carries.
  auto const product = static_cast<unsigned __int128>(operand1ResHigh) * operand2ResLow;
  operand1ResHigh = static_cast<std::uint64_t>(product >> _LimbBits);
  operand2ResLow = static_cast<std::uint64_t>(product);
#else
  auto const low1 = 0x00000000ffffffff & operand1ResHigh;
  auto const high1 = (0xffffffff00000000 & operand1ResHigh) >> 32;
  auto const low2 = 0x00000000ffffffff & operand2ResLow;
  auto const high2 = (0xffffffff00000000 & operand2ResLow) >> 32;

  auto const ll = low1 * low2;
  auto const hh = high1 * high2;

  auto const lh = low1 * high2;
  auto const hl = high1 * low2;

  auto const lhh = (lh & 0xffffffff00000000) >> 32;
  auto const lhl = (lh & 0x00000000ffffffff) << 32;

  auto const hlh = (hl & 0xffffffff00000000) >> 32;
  auto const hll = (hl & 0x00000000ffffffff) << 32;

  auto resL = lhl;
  auto resH = lhh;
  resH += hlh;
  auto carry = false;
  AddUintWithCarry(resL, hll, carry);
  if (carry) {
    ++resH;
    carry = false;
  }
  AddUintWithCarry(resL, ll, carry);
  AddUintWithCarry(resH, hh, carry);
  operand1ResHigh = resH;
  operand2ResLow = resL;
#endif
}

auto numex::BigInt::operator ++() -> BigInt& {
  *this += 1;
  return *this;
}

auto numex::BigInt::operator ++(int) -> BigInt {
  auto b = *this;
  *this += 1;
  return b;
}

auto numex::BigInt::operator -(BigInt const &a) const -> BigInt {
  auto b = *this;
  b -= a;
  return b;
}

auto numex::BigInt::operator -(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b -= a;
  return b;
}

auto numex::BigInt::operator -=(BigInt const &a) -> BigInt& {
  auto aa = a;
  aa = -aa;
  *this += aa;
  return *this;
}

auto numex::BigInt::operator -=(std::int64_t const a) -> BigInt& {
  if (a == std::numeric_limits<std::int64_t>::min()) {
    *this += -BigInt(a);
    return *this;
  }
  *this += -a;
  return *this;
}

auto numex::BigInt::operator --() -> BigInt& {
  *this -= 1;
  return *this;
}

auto numex::BigInt::operator --(int) -> BigInt {
  auto b = *this;
  *this -= 1;
  return b;
}

auto numex::BigInt::operator /(BigInt const &a) const -> BigInt {
  auto b = *this;
  b /= a;
  return b;
}

auto numex::BigInt::operator /(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b /= a;
  return b;
}

auto numex::BigInt::operator /=(BigInt const &a) -> BigInt& {
  auto c = *this;
  auto res = BigInt();

  _Div(c, res, a);

  this->_Number = res._Number;
  return *this;
}

auto numex::BigInt::operator /=(std::int64_t const a) -> BigInt& {
  auto c = *this;
  auto res = BigInt();

  _Div(c, res, BigInt(a));

  this->_Number = res._Number;
  return *this;
}

auto numex::BigInt::operator %(BigInt const &a) const -> BigInt {
  auto b = *this;
  b %= a;
  return b;
}

auto numex::BigInt::operator %(std::int64_t const a) const -> BigInt {
  auto b = *this;
  b %= a;
  return b;
}

auto numex::BigInt::operator %=(BigInt const &a) -> BigInt& {
  auto c = *this;
  auto res = BigInt();

  _Div(c, res, a);

  this->_Number = c._Number;
  return *this;
}

auto numex::BigInt::operator %=(std::int64_t const a) -> BigInt& {
  auto c = *this;
  auto res = BigInt();

  _Div(c, res, BigInt(a));

  this->_Number = c._Number;
  return *this;
}

auto numex::BigInt::AddUintWithCarry(std::uint64_t &operand1res, std::uint64_t const operand2,
  bool &carry) const -> void {
  auto const partial = operand1res + operand2;
  auto const carriedPartial = partial < operand1res;
  auto const result = partial + static_cast<std::uint64_t>(carry);
  carry = carriedPartial || result < partial;
  operand1res = result;
}

auto numex::BigInt::_AddUintAt(std::uint64_t index, std::uint64_t const operand) -> void {
  auto carry = false;
  AddUintWithCarry(_Number[index], operand, carry);
  while (carry) {
    ++index;
    if (_Number[index] != static_cast<std::uint64_t>(-1)) {
      ++_Number[index];
      break;
    }
    _Number[index] = 0;
  }
}

auto numex::BigInt::_Div(std::uint64_t const &dividend, std::uint64_t const &divisor,
  std::uint64_t &prevRmd) const -> std::uint64_t {
  if (divisor == 0) {
    throw std::invalid_argument("Division by zero!");
  }

  auto quot = static_cast<std::uint64_t>(0);
  auto rmd = static_cast<std::uint64_t>(0);

  if (prevRmd) {
    quot = static_cast<std::uint64_t>(-1) / divisor;
    rmd = static_cast<std::uint64_t>(-1) % divisor + 1;
    if (rmd == divisor) {
      ++quot;
      rmd = 0;
    }

    quot *= prevRmd;
    rmd *= prevRmd;
  }

  quot += dividend / divisor;
  rmd += dividend % divisor;

  quot += rmd / divisor;
  rmd %= divisor;

  prevRmd = rmd;
  return quot;
}

auto numex::BigInt::_Div(BigInt &rmdDividend, BigInt &resQuot, BigInt const &divisor) const -> void {
  if (divisor == 0) {
    throw std::invalid_argument("Division by zero!");
  }

  auto &a = rmdDividend;
  auto d = divisor;
  auto &c = resQuot;

  auto const negDividend = a.IsNegative();
  auto const negQuot = negDividend != d.IsNegative();

  if (negDividend) {
    a = -a;
  }

  if (d.IsNegative()) {
    d = -d;
  }

  if (a < d) {
    if (negDividend) { a = -a; }
    return;
  }

  auto const dvsr = d;
  auto &dnum = d._Number;

  auto const diff = a._Number.size() - dnum.size();
  for (auto i = diff; i != 0; --i) {
    dnum.insert(dnum.begin(), 0);
  }

  while (a >= d) {
    d <<= 1;
  }

  while (d > a) {
    d >>= 1;
  }

  while (d >= dvsr) {
    c <<= 1;
    if (d <= a) {
      c._Number[0] |= 1;
      a -= d;
    }
    d >>= 1;
  }

  if (negQuot) {
    c = -c;
  }

  if (negDividend) {
    a = -a;
  }
}

auto numex::BigInt::operator -() const -> BigInt {
  auto r = *this;
  r = ~r + 1;
  return r;
}

auto operator +(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return b + a;
}

auto operator -(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return -(b - a);
}

auto operator *(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  return b * a;
}

auto operator /(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  auto const aa = numex::BigInt(a);
  return aa / b;
}

auto operator %(std::int64_t const a, numex::BigInt const &b) -> numex::BigInt {
  auto const aa = numex::BigInt(a);
  return aa % b;
}

auto numex::BigInt::operator >>(std::uint64_t const shift) const -> BigInt {
  auto b = *this;
  b >>= shift;
  return b;
}

auto numex::BigInt::operator >>=(std::uint64_t const shift) -> BigInt& {
  auto const neg = IsNegative();
  auto sh = shift;

  if (sh >= _LimbBits) {
    auto const q = sh / _LimbBits;
    sh %= _LimbBits;
    if (q >= _Number.size()) {
      _Number.assign(1, neg ? ~std::uint64_t{0} : std::uint64_t{0});
      return *this;
    }
    _Number.erase(_Number.begin(), _Number.begin() + static_cast<std::ptrdiff_t>(q));
  }

  if (sh == 0) {
    _EraseLeadingSign();
    return *this;
  }

  auto const mask = (std::uint64_t{1} << sh) - 1;
  auto const maskShift = _LimbBits - sh;
  auto carry = std::uint64_t{0};

  for (auto &limb : _Number | std::views::reverse) {
    auto const nextCarry = limb & mask;
    limb >>= sh;
    if (carry) limb |= carry << maskShift;
    carry = nextCarry;
  }

  if (neg) _Number.back() |= ~std::uint64_t{0} << maskShift;

  _EraseLeadingSign();
  return *this;
}

auto numex::BigInt::_URShift(std::uint64_t const shift) -> BigInt& {
  auto sh = shift;

  if (sh >= _LimbBits) {
    auto const q = sh / _LimbBits;
    sh %= _LimbBits;
    if (q >= _Number.size()) {
      _Number.assign(1, std::uint64_t{0});
      return *this;
    }
    _Number.erase(_Number.begin(), _Number.begin() + static_cast<std::ptrdiff_t>(q));
  }

  if (sh == 0) {
    _EraseLeadingSign();
    return *this;
  }

  auto const mask = (std::uint64_t{1} << sh) - 1;
  auto const maskShift = _LimbBits - sh;
  auto carry = std::uint64_t{0};

  for (auto &limb : _Number | std::views::reverse) {
    auto const nextCarry = limb & mask;
    limb >>= sh;
    if (carry) limb |= carry << maskShift;
    carry = nextCarry;
  }

  _EraseLeadingSign();
  return *this;
}

auto numex::BigInt::operator <<(std::uint64_t const shift) const -> BigInt {
  auto b = *this;
  b <<= shift;
  return b;
}

auto numex::BigInt::operator <<=(std::uint64_t const shift) -> BigInt& {
  auto sh = shift;
  auto q = std::uint64_t{0};
  if (sh >= _LimbBits) {
    q = sh / _LimbBits;
    sh %= _LimbBits;
  }
  auto const neg = IsNegative();

  if (sh != 0) {
    auto const maskShift = _LimbBits - sh;
    auto const mask = ~(~std::uint64_t{0} >> sh);
    auto carry = std::uint64_t{0};

    for (auto &limb : _Number) {
      auto const nextCarry = limb & mask;
      limb <<= sh;
      if (carry) limb |= carry >> maskShift;
      carry = nextCarry;
    }

    if (carry) {
      auto const sign = (neg ? ~std::uint64_t{0} : std::uint64_t{0}) << sh;
      _Number.push_back((carry >> maskShift) | sign);
    }
  }

  if (neg != IsNegative()) {
    _Number.push_back(neg ? ~std::uint64_t{0} : std::uint64_t{0});
  }

  if (q != 0) {
    _Number.insert(_Number.begin(), q, std::uint64_t{0});
  }

  _EraseLeadingSign();
  return *this;
}

auto numex::BigInt::operator ==(BigInt const &b) const -> bool {
  return _Number == b._Number;
}

auto numex::BigInt::operator <=>(BigInt const &b) const -> std::strong_ordering {
  auto const neg = IsNegative();
  auto const negB = b.IsNegative();
  if (neg != negB) return neg ? std::strong_ordering::less : std::strong_ordering::greater;

  auto const &n = b._Number;
  if (_Number.size() != n.size()) {
    return (_Number.size() > n.size()) != neg
      ? std::strong_ordering::greater
      : std::strong_ordering::less;
  }

  for (auto i = n.size(); i-- > 0;) {
    if (_Number[i] != n[i]) return _Number[i] <=> n[i];
  }

  return std::strong_ordering::equal;
}

auto numex::BigInt::operator ==(std::int64_t const a) const -> bool {
  if (_Number.size() != 1) return false;
  return _Number[0] == static_cast<std::uint64_t>(a);
}

auto numex::BigInt::operator <=>(std::int64_t const a) const -> std::strong_ordering {
  auto const neg = IsNegative();
  auto const negA = a < 0;
  if (neg != negA) return neg ? std::strong_ordering::less : std::strong_ordering::greater;
  if (_Number.size() > 1) return neg ? std::strong_ordering::less : std::strong_ordering::greater;
  return _Number[0] <=> static_cast<std::uint64_t>(a);
}

auto numex::BigInt::Abs() const -> BigInt {
  return IsNegative() ? -*this : *this;
}

auto numex::BigInt::Max(BigInt const &b) const -> BigInt {
  return *this < b ? b : *this;
}

auto numex::BigInt::Min(BigInt const &b) const -> BigInt {
  return b < *this ? b : *this;
}

auto numex::BigInt::Pow(std::uint64_t exp) const -> BigInt {
  auto temp = BigInt(1);
  if (exp == 0) return temp;

  auto b = *this;
  while (exp > 1) {
    if (exp & 1) {
      temp *= b;
    }
    b *= b;
    exp >>= 1;
  }

  return b * temp;
}

auto numex::BigInt::ModPow(const std::uint64_t exp, std::uint64_t const mod) const -> BigInt {
  auto ret = BigInt();
  if (mod == 1) return ret;
  ret = BigInt(1);

  auto b = *this;
  auto x = _FromUnsigned(exp);
  auto const modulus = _FromUnsigned(mod);

  b %= modulus;
  while (x > 0) {
    if ((x & 1) == 1) {
      ret *= b;
      ret %= modulus;
    }
    x >>= 1;
    b *= b;
    b %= modulus;
  }

  return ret;
}

auto numex::BigInt::Fact(std::uint64_t const a) -> BigInt {
  auto ret = BigInt(1);
  if (a <= 1) return ret;
  if (a == 2) return _FromUnsigned(a);

  auto c = a;
  auto sum = static_cast<std::uint64_t>(0);
  auto bitc = std::vector<std::uint64_t>();

  while (c != 1) {
    bitc.push_back((c - 1) | 1);
    c >>= 1;
    sum += c;
  }

  auto prev = static_cast<std::uint64_t>(1);
  auto result = BigInt(1);

  for (auto const value : bitc | std::views::reverse) {
    result *= _OddFact(value, prev + 2);
    ret *= result;
    prev = value;
  }

  ret <<= sum;
  return ret;
}

auto numex::BigInt::_OddFact(std::uint64_t const a, std::uint64_t const begin) -> BigInt {
  auto ret = BigInt(1);
  if (a < 3) {
    return ret;
  }
  if (a == 3) {
    return _FromUnsigned(a);
  }

  auto n = (a - 1) | 1;
  if ((n - begin) % 4 == 0) {
    ret = _FromUnsigned(n);
    n -= 2;
  }

  auto last = _FromUnsigned(n + 2);
  last *= _FromUnsigned(begin - 2);

  for (auto m = (n - begin + 2) * 2; m >= 4; m -= 8) {
    last += _FromUnsigned(m);
    ret *= last;
  }

  return ret;
}

auto numex::BigInt::_CountTrailingZeros() const -> std::uint64_t {
  auto zeros = std::uint64_t{0};
  for (auto const limb : _Number) {
    if (limb != 0) {
      return zeros + static_cast<std::uint64_t>(std::countr_zero(limb));
    }
    zeros += _LimbBits;
  }
  return zeros; // the value is zero; every bit is a trailing zero
}

auto numex::BigInt::Gcd(BigInt const &b) const -> BigInt {
  auto aa = *this;
  auto bb = b;

  if (aa < 0) {
    aa = -aa;
  }
  if (bb < 0) {
    bb = -bb;
  }

  if (aa == 0) return bb;
  if (bb == 0) return aa;

  // Stein's algorithm: shifts, comparisons and subtractions only. The Euclidean
  // form needed a full bit-at-a-time long division for every step.
  auto const aZeros = aa._CountTrailingZeros();
  auto const bZeros = bb._CountTrailingZeros();
  auto const commonTwos = std::min(aZeros, bZeros);

  aa >>= aZeros;
  do {
    bb >>= bb._CountTrailingZeros();
    if (aa > bb) {
      std::swap(aa, bb);
    }
    bb -= aa; // both are odd here, so the difference is even and shrinks
  }
  while (bb != 0);

  return aa << commonTwos;
}

auto numex::BigInt::Lcm(BigInt const &b) const -> BigInt {
  auto const c = *this * b / Gcd(b);
  if (c < 0) return -c;
  return c;
}

auto numex::BigInt::Fib(std::uint64_t const a) -> BigInt {
  if (a < 2) return _FromUnsigned(a);

  auto c = a;
  auto bitc = std::vector<bool>();

  while (c != 1) {
    bitc.push_back((c & 1) != 0);
    c >>= 1;
  }

  auto fn = BigInt(1);
  auto fn1 = BigInt(1);
  auto temp = BigInt();

  for (auto const bit : bitc | std::views::reverse) {
    temp = fn * (fn1 * 2 - fn);
    fn1 = fn1 * fn1 + fn * fn;
    if (bit) {
      fn = fn1;
      fn1 += temp;
    }
    else {
      fn = temp;
    }
  }

  return fn;
}
