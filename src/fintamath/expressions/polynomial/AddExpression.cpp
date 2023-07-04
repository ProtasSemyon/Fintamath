#include "fintamath/expressions/polynomial/AddExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

AddExpression::AddExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(Add(), inChildren) {
}

std::string AddExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  ArgumentPtr child = inChild;
  bool isChildNegated = false;

  if (auto negExpr = cast<IExpression>(inChild); negExpr && is<Neg>(negExpr->getFunction())) {
    child = negExpr->getChildren().front();
    isChildNegated = true;
  }

  std::string result = child->toString();

  if (!isChildNegated && result.size() > 1 && result.front() == Neg().toString().front()) {
    isChildNegated = true;
    result = result.substr(1, result.size() - 1);
  }

  std::string funcStr;

  if (isChildNegated) {
    funcStr = Sub().toString();
  }
  else if (prevChild) {
    funcStr = Add().toString();
  }

  if (!funcStr.empty()) {
    if (prevChild) {
      funcStr = putInSpaces(funcStr);
    }

    result = funcStr + result;
  }

  return result;
}

int AddExpression::comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr && is<Div>(lhsExpr->getFunction()) && (!rhsExpr || !is<Div>(rhsExpr->getFunction()))) {
    return 1;
  }

  if (rhsExpr && is<Div>(rhsExpr->getFunction()) && (!lhsExpr || !is<Div>(lhsExpr->getFunction()))) {
    return -1;
  }

  return IPolynomExpression::comparator(lhs, rhs);
}

AddExpression::SimplifyFunctionsVector AddExpression::getFunctionsForSimplify() const {
  static const AddExpression::SimplifyFunctionsVector simplifyFunctions = {
      &AddExpression::simplifyNumbers,       //
      &AddExpression::sumRates,              //
      &AddExpression::simplifyLogarithms,    //
      &AddExpression::simplifyMulLogarithms, //
  };
  return simplifyFunctions;
}

AddExpression::SimplifyFunctionsVector AddExpression::getFunctionsForPreSimplify() const {
  static const AddExpression::SimplifyFunctionsVector simplifyFunctions = {
      &AddExpression::simplifyNegations, //
  };
  return simplifyFunctions;
}

AddExpression::SimplifyFunctionsVector AddExpression::getFunctionsForPostSimplify() const {
  static const AddExpression::SimplifyFunctionsVector simplifyFunctions = {
      &AddExpression::sumDivisions, //
  };
  return simplifyFunctions;
}

ArgumentPtr AddExpression::simplifyNumbers(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                           const ArgumentPtr &rhsChild) {
  if (*lhsChild == Integer(0)) {
    return rhsChild;
  }
  if (*rhsChild == Integer(0)) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr AddExpression::simplifyNegations(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Neg>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return std::make_shared<Integer>(0);
  }

  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Neg>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return std::make_shared<Integer>(0);
  }

  return {};
}

ArgumentPtr AddExpression::simplifyLogarithms(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                              const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr || !is<Log>(lhsExpr->getFunction()) || !is<Log>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  if (*lhsChildren.front() == *rhsChildren.front()) {
    return makeExpr(Log(), lhsChildren.front(), makeExpr(Mul(), lhsChildren.back(), rhsChildren.back()))
        ->toMinimalObject();
  }

  return {};
}

ArgumentPtr AddExpression::simplifyMulLogarithms(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                                 const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr) {
    return {};
  }

  if (is<Mul>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    ArgumentsPtrVector lhsExprChildren = lhsExpr->getChildren();
    ArgumentsPtrVector rhsExprChildren = rhsExpr->getChildren();

    std::vector<size_t> lhsLogarithmsIndexes = findLogarithms(lhsExprChildren);
    std::vector<size_t> rhsLogarithmsIndexes = findLogarithms(rhsExprChildren);

    for (size_t i : lhsLogarithmsIndexes) {
      auto lhsLogExpr = cast<IExpression>(lhsExprChildren[i]);

      for (size_t j : rhsLogarithmsIndexes) {
        auto rhsLogExpr = cast<IExpression>(rhsExprChildren[j]);

        if (*lhsLogExpr->getChildren().front() == *rhsLogExpr->getChildren().front()) {
          lhsLogExpr = cast<IExpression>(mulToLogarithm(lhsExprChildren, i));
          rhsLogExpr = cast<IExpression>(mulToLogarithm(rhsExprChildren, j));

          return makeExpr(Log(), lhsLogExpr->getChildren().front(),
                          makeExpr(Mul(), lhsLogExpr->getChildren().back(), rhsLogExpr->getChildren().back()))
              ->toMinimalObject();
        }
      }
    }
  }

  std::shared_ptr<const IExpression> mulExpr;
  std::shared_ptr<const IExpression> logExpr;

  if (is<Mul>(lhsExpr->getFunction()) && is<Log>(rhsExpr->getFunction())) {
    mulExpr = lhsExpr;
    logExpr = rhsExpr;
  }
  else if (is<Mul>(rhsExpr->getFunction()) && is<Log>(lhsExpr->getFunction())) {
    mulExpr = rhsExpr;
    logExpr = lhsExpr;
  }
  else {
    return {};
  }

  ArgumentsPtrVector mulExprChildren = mulExpr->getChildren();
  std::vector<size_t> logarithmsIndexes = findLogarithms(mulExprChildren);

  for (size_t i : logarithmsIndexes) {
    auto childLogExpr = cast<IExpression>(mulExprChildren[i]);

    if (*childLogExpr->getChildren().front() == *logExpr->getChildren().front()) {
      childLogExpr = mulToLogarithm(mulExprChildren, i);
      return makeExpr(Log(), logExpr->getChildren().front(),
                      makeExpr(Mul(), logExpr->getChildren().back(), childLogExpr->getChildren().back()))
          ->toMinimalObject();
    }
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> AddExpression::getRateValuePair(const ArgumentPtr &inChild) {
  ArgumentPtr rate;
  ArgumentPtr value;

  if (const auto mulExpr = cast<IExpression>(inChild); mulExpr && is<Mul>(mulExpr->getFunction())) {
    const ArgumentsPtrVector mulExprChildren = mulExpr->getChildren();

    if (is<INumber>(mulExprChildren.front())) {
      rate = mulExprChildren.front();

      if (mulExprChildren.size() == 2) {
        value = mulExprChildren[1];
      }
      else {
        value =
            makeExpr(Mul(), ArgumentsPtrVector(mulExprChildren.begin() + 1, mulExprChildren.end()))->toMinimalObject();
      }
    }
  }
  else if (const auto negExpr = cast<IExpression>(inChild); negExpr && is<Neg>(negExpr->getFunction())) {
    rate = std::make_shared<Integer>(-1);
    value = negExpr->getChildren().front();
  }

  if (rate == nullptr || value == nullptr) {
    rate = std::make_shared<Integer>(1);
    value = inChild;
  }

  return {rate, value};
}

ArgumentPtr AddExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeExpr(Add(), rates);
  return makeExpr(Mul(), ratesSum, value)->toMinimalObject();
}

std::vector<size_t> AddExpression::findLogarithms(const ArgumentsPtrVector &children) {
  std::vector<size_t> indexes;

  for (size_t i = 0; i < children.size(); i++) {
    if (const auto childExpr = cast<const IExpression>(children[i]); childExpr && is<Log>(childExpr->getFunction())) {

      indexes.emplace_back(i);
    }
  }

  return indexes;
}

std::shared_ptr<const IExpression> AddExpression::mulToLogarithm(const ArgumentsPtrVector &children, size_t i) {
  ArgumentsPtrVector mulChildren = children;
  auto logExpr = cast<const IExpression>(mulChildren[i]);

  mulChildren.erase(mulChildren.begin() + ArgumentsPtrVector::difference_type(i));

  const ArgumentPtr powRate = mulChildren.size() > 1 ? makeExpr(Mul(), mulChildren) : mulChildren.front();
  const ArgumentPtr powExpr = makeExpr(Pow(), logExpr->getChildren().back(), powRate);

  return cast<IExpression>(makeExpr(Log(), logExpr->getChildren().front(), powExpr));
}

ArgumentPtr AddExpression::sumRates(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                    const ArgumentPtr &rhsChild) {
  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr AddExpression::sumDivisions(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                        const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && //
      is<Div>(lhsExpr->getFunction()) && is<Div>(rhsExpr->getFunction()) &&
      *lhsExpr->getChildren().back() == *rhsExpr->getChildren().back()) {
    return makeExpr(Div(),
                    makeExpr(Add(), lhsExpr->getChildren().front(), rhsExpr->getChildren().front())->toMinimalObject(),
                    lhsExpr->getChildren().back());
  }

  return {};
}

}