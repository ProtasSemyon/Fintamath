#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

IPolynomExpression::IPolynomExpression(const IPolynomExpression &rhs)
    : std::enable_shared_from_this<IPolynomExpression>(rhs),
      func(cast<IFunction>(rhs.func->clone())),
      children(rhs.children) {
}

IPolynomExpression &IPolynomExpression::operator=(const IPolynomExpression &rhs) {
  if (&rhs != this) {
    func = cast<IFunction>(rhs.func->clone());
    children = rhs.children;
  }

  return *this;
}

IPolynomExpression::IPolynomExpression(const IFunction &func, ArgumentsPtrVector children)
    : func(cast<IFunction>(func.clone())),
      children(std::move(children)) {
  compress();
}

void IPolynomExpression::pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to) {
  for (const auto &elem : from) {
    to.emplace_back(elem);
  }
}

std::shared_ptr<IFunction> IPolynomExpression::getFunction() const {
  return func;
}

const ArgumentsPtrVector &IPolynomExpression::getArgumentsPtrVector() const {
  return children;
}

void IPolynomExpression::setPrecision(uint8_t precision) {
  for (auto &child : children) {
    if (auto expr = cast<IExpression>(child)) {
      expr->setPrecision(precision);
      return;
    }

    if (const auto constant = cast<IConstant>(child)) {
      child = (*constant)();
    }

    if (is<INumber>(child)) {
      child = std::make_shared<Real>(convert<Real>(*child).precise(precision));
    }
  }
}

ArgumentsPtrVector IPolynomExpression::getVariables() const {
  ArgumentsPtrVector vars;

  for (const auto &child : children) {
    if (is<Variable>(child)) {
      vars.emplace_back(child);
      continue;
    }

    if (const auto childExpr = cast<IExpression>(child)) {
      auto childVars = childExpr->getVariables();

      for (const auto &childVar : childVars) {
        vars.emplace_back(childVar);
      }

      continue;
    }
  }

  return vars;
}

ArgumentsPtrVector IPolynomExpression::getPolynom() const {
  return children;
}

std::shared_ptr<IMathObject> IPolynomExpression::simplify() {
  for (auto &child : children) {
    simplifyChild(child);
  }

  return simplifyRec();
}

std::shared_ptr<IMathObject> IPolynomExpression::simplifyRec() {
  size_t childrenSize = children.size();

  for (int64_t i = 0; i < children.size() - 1; i++) {
    for (int64_t j = i + 1; j < children.size(); j++) {
      if (func->isNonExressionEvaluatable() && func->doArgsMatch({*children[i], *children[j]})) {
        children[i] = (*func)(*children[i], *children[j]);
        children.erase(children.begin() + j);
        continue;
      }

      if (auto res = simplifyChildren(children[i], children[j])) {
        children[i] = res;
        children.erase(children.begin() + j);
        continue;
      }
    }
  }

  if (children.size() == 1) {
    return children.front();
  }

  if (children.size() != childrenSize) {
    return simplifyRec();
  }

  return shared_from_this();
}

void IPolynomExpression::validate() const {
  for (const auto &child : children) {
    if (const auto childExpr = cast<IExpression>(child)) {
      childExpr->validate();
    }
  }

  const auto func = this->getFunction();

  for (size_t i = 1; i < children.size(); i++) {
    this->validateArgs(*func, {children[i - 1], children[i]});
  }
}

void IPolynomExpression::sortVector(ArgumentsPtrVector &vector,
                                    std::map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
                                    ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector) {
  for (auto &child : vector) {
    if (const auto expr = cast<IExpression>(child)) {
      if (const auto op = cast<IOperator>(expr->getFunction())) {
        priorityMap[op->getOperatorPriority()].emplace_back(child);
        continue;
      }
      functionVector.emplace_back(child);
      continue;
    }

    if (is<Variable>(child)) {
      variableVector.emplace_back(child);
    }
  }
}

}