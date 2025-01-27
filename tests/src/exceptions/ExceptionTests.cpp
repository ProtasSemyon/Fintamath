#include <gtest/gtest.h>

#include "fintamath/exceptions/Exception.hpp"

#include "fintamath/core/IMathObject.hpp"

using namespace fintamath;

namespace {

class TestMathObject : public IMathObjectCRTP<TestMathObject> {
public:
  void throwException() const {
    throw Exception();
  }
};

}

TEST(ExceptionTests, whatTests) {
  try {
    TestMathObject().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Something went wrong...");
  }
}
