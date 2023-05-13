#include "fintamath/functions/powers/Root.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

static std::pair<Integer, Integer> root(Integer lhs, Integer rhs) {
  // TODO! this algorithm is too slow
  Integer i = 2;
  Integer sq = 1;
  Integer k = 4;
  Integer p = 1;

  while (k <= lhs) {
    if (lhs % i == 0) {
      if (lhs % k == 0) {
        lhs /= k;
        sq *= i;
      }
      else {
        lhs /= i;
        p *= i;
      }
    }
    else {
      i += 1;
    }
    k = i * i;
  }

  return {sq, lhs * p};
}

std::unique_ptr<IMathObject> Root::call(const ArgumentsRefVector &argsVect) const {
  static const auto multiRoot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiRoot;

    outMultiRoot.add<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      auto [outsideRoot, insideRoot] = root(lhs, rhs);
      return makeExpr(Add(), {outsideRoot, *makeExpr(Root(), {insideRoot, rhs})});
    });

    // outMultiRoot.add<Rational>([](const Rational &rhs) {
    //   Integer remainder;

    //   Integer numerator = root(rhs.numerator(), remainder);
    //   if (remainder != 0) {
    //     return root(convert<Real>(rhs)).toMinimalObject();
    //   }

    //   Integer denominator = root(rhs.denominator(), remainder);
    //   if (remainder != 0) {
    //     return root(convert<Real>(rhs)).toMinimalObject();
    //   }

    //   return Rational(numerator, denominator).toMinimalObject();
    // });

    // outMultiRoot.add<Real>([](const Real &rhs) {
    //   return std::make_unique<Real>(root(rhs));
    // });

    return outMultiRoot;
  }();

  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  return multiRoot(lhs, rhs);
}

}
