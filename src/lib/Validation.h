/* Description: Pragrama 1 de Calidad de Software. This class handles all the validations
 * that the FileManager needs to have. It validates ll types of things like names, files status,
 * isEmpty, line by line etc.
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Ago-20-2018
 */

#include <iostream>
#include <fstream>

using namespace std;

/* This class validates anything FileManager needs
 * Parameters: none
 * Returns: none
 */
class Validation
{
public:
  // Constructor
    Validation();
  // Validates that the file was opened correctly and exists
    void isOpen ( int );
  // Validates is the file is empty or not
    void isEmpty ( fstream& );
  // Validates that the lines of code, blank lines and comments are counter correctly
    void line ( int *, string );
  // Makes a checksum to validate sum of lines is equal to total lines
    void checksum ( int * );

private:
};

/* Constructor for the validation class which handles everything related to validations
 * Parameters: none
 * Returns: none
 */
Validation::Validation() { }

/* Validates that the file opened correctly
 * Parameters: int fileStatus is the return value of the fstream function to open a file
 * so it checks that 0 is not opened and 1 is opened.
 * Returns: none
 */
void Validation::isOpen( int fileStatus )
{
  if ( !fileStatus )
  {
    throw invalid_argument( "Lo sentimos, ese archivo no existe, intente de nuevo." );
  }
}

/* Validates that the file is NOT empty
 * Parameters: fstream currentFile by reference to read the file and check if empty
 * Returns: none
 */
void Validation::isEmpty( fstream& currentFile )
{
  if( currentFile.peek() < 0 || currentFile.eof() )
  {
    throw invalid_argument( "Lo sentimos, este archivo se encuentra vacio. ("
        + to_string( currentFile.peek() ) + ")" );
  }
}

/* Validates if it is a comment, blank line or code line with the correspongin validations
 * Then adds to the counter array in which the counters of each type of line is stored
 * Parameters: int counter[4] in which all counter for every line type is stored
 * string line is the return value of the getline() function in which will perform the validation and decide what to count
 * Returns: none
 */
void Validation::line( int counters[4], string line )
{
  bool blankLineFlag = true;
  bool codeFlag = false;

  counters[3]++;

  for( int i = 0; i < line.length(); i++ )
  {
    if( line[i] == '/' || line[i] == '*' )
    {
      if( ( i+1 ) <= line.length() )
      {
        if( ( line[i+1] == '/' || line[i+1] == '*' ) || ( line[i] == '*' && isspace(line[i+1] ) ) )
        {
          counters[1]++;
          codeFlag = false;
          blankLineFlag = false;
          break;
        }
      }
    }
    else if( !isspace( line[i] ) && line[i] != '\t' && line[i] != '\n' ) {
      blankLineFlag = false;
      codeFlag = true;
    }
  }

  if( blankLineFlag )
  {
    counters[0]++;
  } else if( codeFlag ) {
    counters[2]++;
  }
}

/* Validates that the sum of all the counters is equal to the amount of lines in the file
 * Parameters: int counter[4] which is the array that stores all the counters for each type of line
 * Returns: none
 */
void Validation::checksum( int counters[4] )
{
  int sum = counters[0] + counters[1] + counters[2];
  if( sum != counters[3] )
  {
    throw invalid_argument( "Checksum does not add" );
  }
}
