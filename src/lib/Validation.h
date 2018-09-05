/* Description: Pragrama 1 de Calidad de Software. This class handles all the validations
 * that the FileManager needs to have. It validates ll types of things like names, files status,
 * isEmpty, line by line etc.
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Ago-20-2018
 */

// Codigo Base
//.b=42
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

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
    int line ( string );//.m
  // Makes a checksum to validate sum of lines is equal to total lines
    void checksum ( int * );
  // Separates file names from whole string
    vector<string> separateFileNames( string );
private:
    // Regular Expression
    regex token; //Matches any token for .b .m .i .d
    regex commentSingleLine;
    regex commentLineStart; // Matches any comment line with // or /*
    regex commentLineEnd; // Matched any ending multicomment line
    regex blankLine; // Matches blank lines
    regex trashLines; //Matches trash lines like { } alone
};

/* Constructor for the validation class which handles everything related to validations
 * Parameters: none
 * Returns: none
 */
Validation::Validation() { //.m
    token = "//(.b=([0-9]+)|.m|.d=([0-9]+)|.i)"; //Matches any token for .b=00 .m .i .d=00
    commentSingleLine = "//|/\\*(.*)\\*/";
    commentLineStart = "/\\*"; // Matches any comment line with // or /*
    commentLineEnd = "\\*/"; // Matched any ending multicomment line
    blankLine = "^[ \t\n]*$"; // Matches blank lines
    trashLines = "(^[ \t\n]*)(\\{|\\})([ \t\n]*$)"; //Matches trash lines like { } alone
}

/* Separates the string in sepearate file names so they can be accessed independently and opened
 * by the FileManager
 * Parameters: String that contains all file names
 * Returns a vector<string> with the separated filenames
 */
vector<string> Validation::separateFileNames( string fileNames)
{
  string fileName = "";
  vector<string> vFileNames;

  for(int i = 0; i <= fileNames.length(); i++)
  {
    // cout << "ASCI=> " << fileNames[i] << " ~ "<< to_string(fileNames[i]).compare("\r") << endl;
    if( to_string(fileNames[i]).compare("\r") == 35 || isspace( fileNames[i] ) || to_string(fileNames[i]) == "38" || to_string(fileNames[i]) == "44" )
    {
      vFileNames.push_back( fileName );
      fileName = "";
    } else {
      fileName += fileNames[i];
    }
  }
  return vFileNames;
}

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
int Validation::line( string line )//.m
{
  //.d=3

  if( regex_search( line, token ) ) { return 0; }

  if( regex_search( line, commentSingleLine ) ) { return 1; }

  if( regex_search( line, commentLineStart ) ) { return 2; }

  if( regex_search( line, commentLineEnd ) ) { return 3; }

  if( regex_search( line, blankLine ) ) { return 4; }

  if( regex_match( line, trashLines ) ) { return 5; }

  //.d=15

  return 6;
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
