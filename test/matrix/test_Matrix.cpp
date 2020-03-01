#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "Matrix.hpp"

using namespace std;
using namespace testing;


class EmptyMatrixFixture : public ::testing::Test {
  protected:
    Matrix m;
};

TEST_F( EmptyMatrixFixture, TEST_MEMBER_VALUES ) {
  // Basic tests with members (row, col, values[][]) 
  ASSERT_EQ( m.getRow(), 0 );
  ASSERT_EQ( m.getCol(), 0 );
  ASSERT_EQ( m.getValues(), nullptr );
}

class SimpleMatrixFixture : public ::testing::Test {
  protected:
    Matrix m;

  public:
    SimpleMatrixFixture() {}

};

TEST_F( SimpleMatrixFixture, TEST_MEMBER_VALUES ) {
  Matrix temp(3, 3);

  // Basic tests with members (row, col, values[][]) 
  ASSERT_EQ( temp.getRow(), 3 );
  ASSERT_EQ( temp.getCol(), 3 );

  // Check for values inside 3x3 array (all 0.0)
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      ASSERT_EQ( temp.getValues()[i][j], 0.0 );
    }
  }

  /* ======= TEST CONSTRUCTORS ============== */

  // Sets all values to j (0, 1, 2) in every row
  for( unsigned int i = 0; i < 3; i++ ) {
    for( unsigned int j = 0; j < 3; j++ ) {
      temp.getValues()[i][j] = j;
    }
  }

  // Tests constructor for equivalence
  Matrix cpy( 3, 3, temp.getValues() );
  ASSERT_EQ( cpy.getRow(), 3 );
  ASSERT_EQ( cpy.getCol(), 3 );
  ASSERT_EQ( temp.valuesAreEqual(temp.getValues(), 
        cpy.getValues(), 3, 3), true );

  // Tests copy constructor for equivalence
  Matrix cpy_with_constructor( cpy );
  ASSERT_EQ( cpy_with_constructor.getRow(), 3 );
  ASSERT_EQ( cpy_with_constructor.getCol(), 3 );
  ASSERT_EQ( cpy.valuesAreEqual(cpy_with_constructor.getValues(), 
        cpy.getValues(), 3, 3), true );

  // Tests for unequivalence
  for( unsigned int i = 0; i < 3; i++ ) {
    for( unsigned int j = 0; j < 3; j++ ) {
      cpy.getValues()[i][j] = 4.1;
    }
  }
  ASSERT_EQ( temp.valuesAreEqual(temp.getValues(), cpy.getValues(), 3, 3),
      false);

  /* =============== TRANSPOSE MATRIX TESTING ================ */

  // Transposing a 3x3 matrix
  Matrix temp_transposed_matrix( 3, 3, temp.transpose().getValues() );
  ASSERT_EQ( temp.valuesAreEqual(temp_transposed_matrix.getValues(), 
        temp.transpose().getValues(), 3, 3), true );

  /* =============== MULTIPLYING MATRIX TESTING ================ */

  // Initializing two 3x3 arrays
  double** arr1 = new double*[3];
  double** arr2 = new double*[3];
  for( int i = 0; i < 3; i++ ) {
    arr1[i] = new double[3];
    arr2[i] = new double[3];
  }

  // Populate arr1 to the following matrix
  /*
     [1, 2, 3
     4, 5, 6
     7, 8, 9]
   */

  int count = 1;
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      arr1[i][j] = count++;
    }
  }

  // Populate arr2 to the following matrix
  /*
     [9, 8, 7
     6, 5, 4
     3, 2, 1]
   */
  count = 9;
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      arr2[i][j] = count--;
    }
  }

  // Multiply the two matrices together to get the resulting matrix product
  Matrix m1( 3, 3, arr1 );
  Matrix m2( 3, 3, arr2 );
  Matrix product = m1 * m2;

  // Test matrix equivalent values
  /*
     [30, 24, 28]
     84, 69, 54
     138, 114, 90]
   */
  ASSERT_EQ( product.getValues()[0][0], 30 );
  ASSERT_EQ( product.getValues()[0][1], 24 );
  ASSERT_EQ( product.getValues()[0][2], 18 );
  ASSERT_EQ( product.getValues()[1][0], 84 );
  ASSERT_EQ( product.getValues()[1][1], 69 );
  ASSERT_EQ( product.getValues()[1][2], 54 );
  ASSERT_EQ( product.getValues()[2][0], 138 );
  ASSERT_EQ( product.getValues()[2][1], 114 );
  ASSERT_EQ( product.getValues()[2][2], 90 );

}

/* Purposely fails to allow print statements into console */
TEST_F( EmptyMatrixFixture, FAIL_TEST ) {
  //ASSERT_EQ( true, false );
}
