/**
 * Filename: matrix.hpp
 * Author: Steven Gov
 * Email: govsteven08@gmail.com
 * Sources: Oracle, Stackoverflow, etc.
 * Summary: Class definition for a matrix of MxN dimensions
 */
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

/**
 * Defines a class for a matrix. Contains basic operations, such as tranpose and
 * mulitplication of two matrix classes
 */
class Matrix {

  private:  

    // Rows and columns
    unsigned int m_rows;
    unsigned int m_cols;
    double** m_values;

  public:

    /**
     * Defualt constructor
     * Initialize an empty Matrix
     */
    Matrix() : m_rows(0), m_cols(0), m_values(nullptr) {}

    /**
     * Constructor to make Matrix
     * Parameter: rows - Matrix rows
     *            cols - Matrix cols
     */
    Matrix( unsigned int rows, unsigned int cols ) {
      m_rows = rows;
      m_cols = cols;

      // Initialize matrix to a pre-defined size of [rows][cols] (w/value 0)
      m_values = new double* [rows];
      for( unsigned int i = 0; i < rows; i++ ) {
        m_values[i] = new double[cols];
      }

      for( unsigned int i = 0; i < rows; i++ ) {
        for( unsigned int j = 0; j < cols; j++ ) {
          m_values[i][j] = 0.0;
        }
      }

    }

    /**
     * Constructor to make Matrix
     * Parameter: rows - Matrix rows
     *            cols - Matrix cols
     *            v - values to be initialized into matrix
     */
    Matrix( unsigned int rows, unsigned int cols, double** v ) {
      m_rows = rows;
      m_cols = cols;

      // Initialize matrix to a pre-defined size of [rows][cols] (w/value 0)
      m_values = new double* [rows];
      for( unsigned int i = 0; i < rows; i++ ) {
        m_values[i] = new double[cols];
      }

      // memcpy( m_values, v, (rows * cols * sizeof(double)) );

      // Copy m into m_values
      for( unsigned int i = 0; i < rows; i++ ) {
        for( unsigned int j = 0; j < cols; j++ ) {
          m_values[i][j] = v[i][j];
        }
      }

    }


    /**
     * Copy constructor
     * Parameter: cpy - copy of a Matrix to transfer data into new Matrix
     */
    Matrix( const Matrix& cpy ) {
      m_rows = cpy.getRow();
      m_cols = cpy.getCol();

      // Initialize matrix to a pre-defined size of [rows][cols] (w/value 0)
      m_values = new double* [m_rows];
      for( unsigned int i = 0; i < m_rows; i++ ) {
        m_values[i] = new double[m_cols];
      }


      // memcpy( m_values, cpy.getValues(), (m_rows * m_cols * sizeof(double)));

      // Copy m into m_values
      for( unsigned int i = 0; i < m_rows; i++ ) {
        for( unsigned int j = 0; j < m_cols; j++ ) {
          m_values[i][j] = cpy.getValues()[i][j];
        }
      }

    }


    /**
     * Deconstructs object
     */
    ~Matrix() {
      // Free each subarray before pointer
      for( unsigned int i = 0; i < m_rows; i++ ) {
        delete [] m_values[i];
      }
      delete [] m_values;

    }


    // ========== Getters of private members - rows, cols, values =========
    unsigned int getRow() const { return m_rows; }

    unsigned int getCol() const { return m_cols; } 

    double** getValues() const { return m_values; }

    // ========= Setters of private members - rows, cols, values ==========
    void setRow( const unsigned int& r ) { m_rows = r; }

    void setCol( const unsigned int& c ) { m_cols = c; }

    void setValues( double**& v, const unsigned int& r, 
        const unsigned int& c ) {
      memcpy( m_values, v, (r * c * sizeof(double)) );
    }

    /**
     * Prints the contents of the matrix 
     */
    void print() const {
      for( unsigned int i = 0; i < m_rows; i++ ) {
        for( unsigned int j = 0; j < m_cols; j++ ) {
          cout << m_values[i][j] << " ";
        }
        cout << endl;
      }
    }

    //============= Operations ==========================================

    /**
     * Multiplication of two matrices if dimensions are compatible
     * Parameters: m - Second matrix to multiply
     */
    Matrix operator* ( Matrix &m ) {  

      // Creates template matrix to return when successfully mulitplied
      Matrix ans( this->getRow(), m.getCol() );
      double** values = ans.getValues();
      double temp = 0.0;

      // Dimensions must be compatible to multiply matrices 
      if( this->getCol() == m.getRow() ) {
        for( unsigned int i = 0; i < this->getRow(); i++ ) { 
          for( unsigned int j = 0; j < m.getCol(); j++ ) {
            temp = 0.0;
            for( unsigned int k = 0; k < this->getCol(); k++ ) {
              temp += this->m_values[i][k] * m.getValues()[k][j];
            }
            values[i][j] = temp;
          }
        }

        ans.setValues( values, this->getRow(), m.getCol() );
        return ans;

      } else {
        // Cannot be mulitiplied - return empty matrix
        Matrix empty_matrix;
        return empty_matrix;
      }
    }

    /**
     * Transposes a matrix while maintaining dimensions 
     */
    Matrix transpose() {

      // Creates a template matrix to be returned as the transposed matrix
      Matrix transposed_matrix( this->getCol(), this->getRow() );

      // Flip rows and cols of a matrix
      for( unsigned int i = 0; i < this->getCol(); i++ ) {
        for( unsigned int j = 0; j < this->getRow(); j++ ) {
          transposed_matrix.getValues()[i][j] = this->getValues()[j][i];
        }
      }
      return transposed_matrix;
    }

    // ============= Helper Methods ==========================================

    /**
     * Helper method to determine if two 2D arrays are equal
     * Parameters: arr1 - array1 to check for equivalence
     *             arr2 - array2 to check for equivalence
     *             row - num of rows in the matrices
     *             col - num of col in the matrices
     */
    static bool valuesAreEqual( double** arr1, double** arr2, unsigned int row,
        unsigned int col ) {

      for( unsigned int i = 0; i < row; i++ ) {
        for( unsigned int j = 0; j < col; j++ ) {

          // First inequivalence of values means values are not equal
          if( arr1[i][j] != arr2[i][j] ) {
            return false;
          }
        }
      }
      return true;
    }
};
#endif
