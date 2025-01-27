#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/parser/Parser.hpp"

#define REQUIRE_COMPARABLES(Lhs, Rhs)                                          \
  template <typename Lhs, typename Rhs,                                        \
            typename = std::enable_if_t<std::is_base_of_v<IComparable, Lhs> && \
                                        std::is_convertible_v<Rhs, Lhs> &&     \
                                        !std::is_same_v<Lhs, Rhs>>>

namespace fintamath {

class IComparable : public IArithmetic {
public:
  friend inline bool operator<(const IComparable &lhs, const IComparable &rhs) {
    return lhs.lessAbstract(rhs);
  }

  friend inline bool operator>(const IComparable &lhs, const IComparable &rhs) {
    return lhs.moreAbstract(rhs);
  }

  friend inline bool operator<=(const IComparable &lhs, const IComparable &rhs) {
    return !lhs.moreAbstract(rhs);
  }

  friend inline bool operator>=(const IComparable &lhs, const IComparable &rhs) {
    return !lhs.lessAbstract(rhs);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IComparable, T>>>
  static void registerType(Parser::Function<std::unique_ptr<IComparable>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<IComparable> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IComparable);
  }

protected:
  virtual bool lessAbstract(const IComparable &rhs) const = 0;

  virtual bool moreAbstract(const IComparable &rhs) const = 0;

private:
  static Parser::Vector<std::unique_ptr<IComparable>, const std::string &> &getParser();
};

template <typename Derived>
class IComparableCRTP : public IComparable {
#define FINTAMATH_I_COMPARABLE_CRTP IComparableCRTP<Derived>
#include "fintamath/core/IComparableCRTP.hpp"
#undef FINTAMATH_I_COMPARABLE_CRTP
};

REQUIRE_COMPARABLES(Lhs, Rhs)
bool operator<(const Lhs &lhs, const Rhs &rhs) {
  return lhs < Lhs(rhs);
}

REQUIRE_COMPARABLES(Rhs, Lhs)
bool operator<(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) < rhs;
}

REQUIRE_COMPARABLES(Lhs, Rhs)
bool operator>(const Lhs &lhs, const Rhs &rhs) {
  return lhs > Lhs(rhs);
}

REQUIRE_COMPARABLES(Rhs, Lhs)
bool operator>(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) > rhs;
}

REQUIRE_COMPARABLES(Lhs, Rhs)
bool operator<=(const Lhs &lhs, const Rhs &rhs) {
  return lhs <= Lhs(rhs);
}

REQUIRE_COMPARABLES(Rhs, Lhs)
bool operator<=(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) <= rhs;
}

REQUIRE_COMPARABLES(Lhs, Rhs)
bool operator>=(const Lhs &lhs, const Rhs &rhs) {
  return lhs >= Lhs(rhs);
}

REQUIRE_COMPARABLES(Rhs, Lhs)
bool operator>=(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) >= rhs;
}

}

#undef REQUIRE_COMPARABLES
