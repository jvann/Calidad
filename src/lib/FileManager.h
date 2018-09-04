/* Description: Pragrama 1 de Calidad de Software. This class is in charge to manage everything
 * that needs to do with files, opening, closing, reading etc. Also calls validations when needed
 * and handles errores realted to files.
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Ago-20-2018
 */

// Codigo Base
//.b=38
#include <iostream>
#include <fstream>
#include <string>
#include "Validation.h"

using namespace std;

/* FileManager class handles all files like opening a file, keeping the file open
 * close the file, call validations and rhandle file errors
 */
class FileManager
{
public:
  // Constructor
    FileManager();
  // Opens files using fstream from c++
    void open( string );
  // Closees files using fstream from c++
    void close();
  // Reads files using fstream from c++
    void read( int * );
    string getName();

private:
  string fileName;
  fstream  currentFile;
  Validation validate;
};

/* Class constructor
 * Parameters: none
 * Returns: nothing
 */
FileManager::FileManager() { }

/* Handles the file opneing and keeping it alive as well as calling corresponding
 * validations to provide checks and error handling
 * Paramteres: fileName will be the string used as a parameter to open a file
 * Returns: void
 */
void FileManager::open( string fileName )
{
  try
  {
    currentFile.open( "./" + fileName );
    validate.isOpen( currentFile.is_open() );
    validate.isEmpty( currentFile );
    this -> fileName = fileName;
  }
  catch ( const invalid_argument& e )
  {
    throw e;
  }
}

/* Closes the currentFile to terminate the reading/writing from the file
 * Parameters: none
 * Returns: void
 */
void FileManager::close()
{
  this -> currentFile.close();
}

/* Reads line by line the opened file for validation and counting lines of code, blank, comments
 * Parameters: int array counter[4] will be the array that contains the counters of the
 * blank, comment and code lines
 * Returns: void
 */
void FileManager::read( int counters[4] )
{
  string line;
  bool flagMultiCommentLine = false;

  try
  {
    while ( !currentFile.eof() )
    {
      counters[3]++;

      getline( currentFile, line );
      //validate.line( line );
      switch( validate.line( line ) )
      {
        case 0:
          // Token add logic here
          break;
        case 1:
          //cout << "COUNTER: " << counters[3]<< "SINGLE COMMENT => " << line << endl;
          counters[1]++;
          break;
        case 2:
          //cout << "COUNTER: " << counters[3]<< "START COMMENT => " << line << endl;
          counters[1]++;
          flagMultiCommentLine = true;
          break;
        case 3:
          //cout << "COUNTER: " << counters[3]<< "ENd COMMENT => " << line << endl;
          counters[1]++;
          flagMultiCommentLine = false;
          break;
        case 4:
          //cout << "COUNTER: " << counters[3]<< "BLANK => " << line << endl;
          counters[0]++;
          break;
        case 5:
          //cout << "COUNTER: " << counters[3]<< "TRASH => " << line << endl;
          counters[2]++;
          break;
        case 6:
          if( flagMultiCommentLine ) { counters[1]++; }
          break;
        default:
          break;
      }
    }

    //validate.checksum( counters );
  }
  catch ( const invalid_argument& e )
  {
    throw e;
  }
}

/* Returns the name of the file as a getter function
 * Parameters: none
 * Returns: string which is the name of the current opened file
 */
string FileManager::getName()
{
  return this -> fileName;
}
