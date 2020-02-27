/**
 * Filename: matrix.hpp
 * Author: Steven Gov
 * Email: govsteven08@gmail.com
 * Sources: Oracle, Stackoverflow, etc.
 * Summary: Class definition for a matrix of MxN dimensions
 */

#define MATRIX_HPP
#include <iostream>

using namespace std;

class Matrix {

  private:  // or should this be protected 

    // Rows and columns
    unsigned int m_rows;
    unsigned int m_cols;
    double m_values[][];

  public:

    /**
     * Defualt constructor
     * Initialize an empty Matrix
     */
    Matrix() : m_rows(0), m_cols(0), m_values[0][0] {}

    /**
     * Constructor to make Matrix
     * Parameter:
     */

    Matrix( unsigned int rows, unsigned int cols, double m[][] ) {
      m_rows = rows;
      m_cols = cols;

      // Copy m into m_values

    }


    /**
     * Copy constructor? (Do I even need this)
     */


    /**
     * Deconstructs object
     */
    ~Matrix() {}


    // Getters of private members - rows, cols, values
    // SHOULD THESE METHODS BE CONSTANT 
    unsigned int getRow() { return m_rows; }

    unsigned int getCol() { return m_cols; } 

    double[][] getValues() { return m_values; }

    // Setters of private members - rows, cols, values
    void setRow( const unsigned int& r ) { m_rows = r; }

    void setCol( const unsigned int& c ) { m_cols = c; }

    void setValues( const double[][]& v ) { m_values = v; }


    /**
     * Prints the contents of the matrix 
     */
    void print() const {
      for( unsigned int i = 0; i < m_rows; i++ ) {
        for( unsigned int j = 0; j < m_cols; j++ ) {
          cout << m_values[i][j];
        }
        cout << endl;
      }
    }

    //============= operations ==========================================

    /**
     * Multiplication of two matrices
     * Parameters: m - Second matrix to multiply
     */
    Matrix operator* ( Matrix const &m ) {  
      Matrix ans( this->getRow(), m.getCol(), 0.0 );

      double temp = 0.0;
      if( this->getCol() == m.getRow() ) {
        for( unsigned int i = 0; i < this->getRow(); i++ ) { 
          for( unsigned int j = 0; j < m.getCol(); j++ ) {
            temp = 0.0;
            for( unsigned int k = 0; k < this->getCol(); k++ ) {
              temp += this->m_values[i][k] * m[k, j];
            }
            ans[i,j] = temp;
            cout << ans[i,j] << " ";
          }
          cout << endl;
        }
        return ans;

      } else {
        Matrix empty_matrix;
        return empty_matrix;
      }
    }

    /**
     * Transposes a matrix
     */
    Matrix transpose() {

      // Creates a template matrix to be returned as the transposed matrix
      double values[][];
      Matrix transposed_matrix( this->getCol(), this->getRow(), values );

      for( unsigned int i = 0; i < this->getCol(); i++ ) {
        for( unsigned int j = 0; j < this->getRow(); j++ ) {
          // transposed_matrix(i,j) = (this->getValues())[j][i];
        }
      }
      return transposed_matrix;
    }

};
#endif
/*
 * 1. Create matrix class
 * 2. Create test files for these matrix files to test matrix build class
 * 3. Start multiplation and transpose stuff later

 - override operator method matrix multiplication
 - transpose method



 - need to fix test stuff
 - need to fix matrix member of this class
 - need to fix compile errors cause there's a lot of them 




 */
