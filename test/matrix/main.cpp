#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Matrix.hpp"

#define NUM_ARGS_FOR_STD_INOUT 1
#define MIN_MATRICES_TO_MULTIPLY 2 

using namespace std;

/**
 * Main driver for running the matrix program. Use the following commands for
 * all of matrix logic.
 * 
 * Commands:
 * POPULATE
 *    Enter dimensions and values to create a new matrix to push onto storage
 * STORAGE
 *    Prints every matrix that exists within storage
 * TRANSPOSE
 *    Transpose a matrix from storage
 * MULTIPLY
 *    Multiply two matrices from storage
 * REMOVE 
 *    Remove a matrix from storage
 * EXIT
 *    Safely exists program
 */
int main() {


  /* Declaration of constant strings commonly used throughout the program */
  const static string GREETINGS_MSG = "GREETINGS! TYPE COMMANDS " 
    "TO VISUALIZE YOUR MATRIX!";
  const static string INVALID_INDEX_NEGATIVE_MSG = "Invalid index. "
    "Index cannot be negative. Exiting command.";
  const static string PROMPT_ROWS_MSG = "Enter the amount of rows for new " 
    "matrix: ";
  const static string PROMPT_COLS_MSG = "Enter the amount of cols for new "
    "matrix: ";
  const static string POPULATION_SUCCESS_MSG = "New matrix inserted! "
    "Printing matrix structure.";
  const static string STORAGE_EMPTY_MSG = "Storage is empty";
  const static string PRINT_STORAGE_SUCCESS_MSG = "All matrices in storage "
    "have been printed out.";
  const static string PROMPT_TRANSPOSE_MSG = "Select the matrix you would "
    "like to transpose: ";
  const static string TRANSPOSE_SUCCESS_MSG = "Transposed matrix at index "
    "! Printing matrix structure.";
  const static string MATRIX_INSERTED_MSG = "Matrix inserted into storage.";
  const static string MATRIX_NOT_INSERTED_MSG = "Matrix was not inserted into "
    "storage.";
  const static string PROMPT_INSERT_INTO_STORAGE_TRANSPOSE_MSG = "Insert the "
    "transposed matrix into the back of the list? Enter a 0 for no and 1 for "
    "yes: ";
  const static string MULTIPLY_ERR_MSG = "There must be at least two "
    "matrices in storage to mulitply. Exiting command.";
  const static string PROMPT_FIRST_MATRIX_MSG = "Select the 1st matrix you "
    "would like to mulitply: ";
  const static string PROMPT_SECOND_MATRIX_MSG = "Select the 2nd matrix you "
    "would like to mulitply: ";
  const static string COMPATIBLE_MATRIX_ERR_MSG = "Cannot multiply matrices "
    "because col1 != row2. Exiting command.";
  const static string PROMPT_INSERT_INTO_STORAGE_MULTIPLY_MSG = "Insert the "
    "product matrix into the back of the list? Enter a 0 for no and 1 for " 
    "yes: ";
  const static string PROMPT_DELETE_MSG = "Enter the matrix you would like " 
    "to delete: ";
  const static string MATRIX_NOT_EXIST_ERR_MSG = "Invalid index. Matrix does "
    "not exist. Exiting command."; 
  const static string FAILED_TO_INSERT_ERR_MSG = "Did not enter correct " 
    "value to insert or avoid insertion. Program will exit and not insert "
    "matrix.";

  istream* in = &cin; 
  ostream* out = &cout;

  /*
     Attempt to do error checking - can't do this without getting warnings for
     main method parameters

  // Checks for number of args passed into command line when running program
  if( argc == NUM_ARGS_FOR_STD_INOUT ) {
  // Initialize input and ouptut to command line
  in = &cin;
  out = &cout;
  } else { 
  cerr << "No arguments should be passed in for program to work" << endl;
  return 1;
  }
   */

  // Creates a vector of matrices for storage throughout duration of program
  vector<Matrix> matrices_storage;

  // Continuously runs program until user ends program
  *out << GREETINGS_MSG << endl;
  while( !in->eof() ) {

    // Takes in user input as commands
    string line;

    getline( *in, line );
    stringstream sstream( line );

    string command;
    sstream >> command;

    /* =================== COMMAND LOGIC ================================ */
    if( command == "POPULATE" ) {

      // Get rows for the new matrix
      *out << PROMPT_ROWS_MSG;
      int row_input;
      cin >> row_input;

      // Error checking: row cannot be a negative number
      if( row_input <= 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      // Get rows for the new matrix
      *out << PROMPT_COLS_MSG;
      int col_input;
      cin >> col_input;

      // Error checking: col cannot be a negative number
      if( col_input <= 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      // Convert to unsigned int to fit with Matrix class
      unsigned int row = (unsigned int)row_input;
      unsigned int col = (unsigned int)col_input;

      // Initialize the values to prepare for population
      double** arr = new double*[row];
      for( unsigned int i = 0; i < row; i++ ) {
        arr[i] = new double[col];
      }

      // Populate values of new matrix with input
      *out << "Enter the values you would like for your " << 
        row << "x" << col << " matrix in the next line" << endl;
      for( unsigned int i = 0; i < row; i++ ) {
        for( unsigned int j = 0; j < col; j++ ) {
          *out << "[" << i << "][" << j << "]: ";
          cin >> arr[i][j];
        }
      }

      // Creates the return matrix, prints, and adds matrix it to storage
      Matrix m( row, col, arr );
      *out << POPULATION_SUCCESS_MSG << endl;
      m.print();
      matrices_storage.push_back( m );

    } else if( command == "STORAGE" ) {

      // No matrices were found in storage 
      if( matrices_storage.size() == 0 ) {
        *out << STORAGE_EMPTY_MSG << endl;
      } else {

        // Prints every matrix in the storage
        for( unsigned int i = 0; i < matrices_storage.size(); i++ ) {
          *out << "Matrix at index " << i << endl;
          matrices_storage.at(i).print();
          *out << endl;
        }
        *out << PRINT_STORAGE_SUCCESS_MSG << endl;
      }

    } else if( command == "TRANSPOSE" ) {

      // No matrices were found in storage 
      if( matrices_storage.size() == 0 ) {
        *out << STORAGE_EMPTY_MSG << endl;
        continue;
      }

      // Selects a matrix to compose from the storage
      *out << PROMPT_TRANSPOSE_MSG << endl;
      int index_input;
      cin >> index_input;

      // Error checking: index cannot be a negative number
      if( index_input < 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      unsigned int index = (unsigned int)index_input;

      // Checks for invalid index  
      if( matrices_storage.size() - 1 < index ) { 
        *out << "Invalid index " << index << ". The size of the matrix " << 
          "storage is " << matrices_storage.size() << ". Exiting command.";
        *out << endl;
      } else {

        // Transpose the matrix and print it out
        Matrix m( matrices_storage.at(index) );
        Matrix m_transposed_matrix = m.transpose();
        *out << TRANSPOSE_SUCCESS_MSG << endl;
        m_transposed_matrix.print();

        // Gives user option to insert transposed_matrix into storage 
        *out << PROMPT_INSERT_INTO_STORAGE_TRANSPOSE_MSG;
        bool should_insert;
        cin >> should_insert;
        if( should_insert ) {
          *out << MATRIX_INSERTED_MSG << endl;
          matrices_storage.push_back( m_transposed_matrix );
        } else if( !should_insert ) {
          *out << MATRIX_NOT_INSERTED_MSG << endl;;
        } else {
          *out << FAILED_TO_INSERT_ERR_MSG << endl;
        }
      }

    } else if( command == "MULTIPLY" ) {

      // No matrices were found in storage 
      if( matrices_storage.size() == 0 ) {
        *out << STORAGE_EMPTY_MSG << endl;
        continue;
      }

      // Error Checking: makes sure there's two matrices to multipy
      if( matrices_storage.size() < MIN_MATRICES_TO_MULTIPLY ) {
        *out << MULTIPLY_ERR_MSG << endl;
        continue;
      } 


      // Allows user to select first matrix from the storage
      *out << PROMPT_FIRST_MATRIX_MSG;
      int index1_input;
      cin >> index1_input;

      // Error checking: index cannot be a negative number
      if( index1_input < 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      // Error checking: index cannot exceed storage size (invalid index)
      unsigned int index1 = (unsigned int)index1_input;
      if( matrices_storage.size() - 1 < index1 ) { 
        *out << "Invalid index " << index1 << ". The size of the matrix " << 
          "storage is " << matrices_storage.size() << ". Exiting command.";
        continue;
      }

      // Allows user to select second matrix from the storage
      *out << PROMPT_SECOND_MATRIX_MSG;
      int index2_input;
      cin >> index2_input;

      // Error checking: index cannot be a negative number
      if( index1_input < 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      // Error checking: index cannot exceed storage size (invalid index)
      unsigned int index2 = (unsigned int)index2_input;
      if( matrices_storage.size() - 1 < index2 ) { 
        *out << "Invalid index " << index2 << ". The size of the matrix " << 
          "storage is " << matrices_storage.size() << ". Exiting command.";
        continue;
      }

      Matrix m1( matrices_storage.at(index1) );
      Matrix m2( matrices_storage.at(index2) );

      // Error Checking: col1 == row2 in order to multiply matrices
      if( m1.getCol() != m2.getRow() ) {
        *out << COMPATIBLE_MATRIX_ERR_MSG << endl;
      } else {

        // Takes product of two chosen matrices and prints product matrix
        Matrix product = m1 * m2;
        *out << "Multiplied matrix" << index1 << " and matrix" << 
          index2 << "! Printing matrix structure." << endl;
        product.print();

        // Gives user option to insert product matrix into storage 
        *out << PROMPT_INSERT_INTO_STORAGE_MULTIPLY_MSG;
        bool should_insert;
        cin >> should_insert;
        if( should_insert ) {
          *out << MATRIX_INSERTED_MSG << endl;
          matrices_storage.push_back( product );
        } else if( !should_insert ) {
          *out << MATRIX_NOT_INSERTED_MSG << endl;;
        } else {
          *out << FAILED_TO_INSERT_ERR_MSG << endl;
        }
      }

    } else if( command == "REMOVE" ) { 

      // No matrices were found in storage 
      if( matrices_storage.size() == 0 ) {
        *out << STORAGE_EMPTY_MSG << endl;
        continue;
      }

      *out << PROMPT_DELETE_MSG;
      int index_input;
      cin >> index_input;

      // Error checking: index cannot be a negative number
      if( index_input < 0 ) {
        *out << INVALID_INDEX_NEGATIVE_MSG << endl;
        continue;
      }

      // Check if valid index
      unsigned int index = (unsigned int)index_input;
      if( matrices_storage.size() - 1 < index ) { 
        *out << MATRIX_NOT_EXIST_ERR_MSG << endl;
        continue;
      }

      // Deletes matrices_storage[index]
      matrices_storage.erase( matrices_storage.begin() + index );
      *out << "Deleted matrix" << index << "." << endl;

    } else if( command == "EXIT" ) {
      break;
    } /* attempt to do error checking in commands
         else if( command.at(0) != '\n' ) {
    // User has typed an incorrect command
       *out << "Invalid command. Please type command correct " << 
       "(it is case sensitive)" << endl;
       }*/
  }
  return 0;
}
