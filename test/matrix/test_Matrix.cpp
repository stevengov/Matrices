#include <iostream>
#include <gtest/gtest.h>
#include "Matrix.hpp"

using namespace std;
using namespace testing;


class EmptyMatrixFixture : public ::testing::Test {
  protected:
    Matrix m;

  public:
    EmptyMatrixFixture() {
    // initialize stuff here

    }

};

TEST_F( EmptyMatrixFixture, EMPTY_SIZE_TEST ) {
  // write some basic tests with members here

}
