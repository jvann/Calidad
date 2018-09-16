/* Description: Pragrama 1 de Calidad de Software. This class handles all the validations
 * that the FileManager needs to have. It validates ll types of things like names, files status,
 * isEmpty, line by line etc.
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Sep-15-2018
 */

// Codigo Base
//.b=42
#include <iostream>
#include <fstream>
#include <sstream>
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
    int *line ( string );//.m
    // Makes a checksum to validate sum of lines is equal to total lines
    void checksum ( int * );
    // Separates file names from whole string
    vector<string> separateFileNames( string );
    // Returns name with no extension
    string nameWithNoExt( string );

private:
    // Regular Expression
    regex tokenB; //Matches any token for .b
    regex tokenD; //Matches any token for .d
    regex tokenM; //Matches any token for .m
    regex tokenI; //Matches any token for .i
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

    //Tokens
    tokenB = "\\/\\/\\.b=([0-9]+)"; //Matches any token for //.d=00
    tokenD = "\\/\\/\\.d=([0-9]+)"; //Matches any token for //.b=00
    tokenM = "(.)*(\\/\\/\\.m)(\t|\n|\r|\v| )*"; //Matches any token for //.m
    tokenI = "(\\/\\/\\.i)"; //Matches any token for //.i

    //Lines
    commentSingleLine = "^((\t|\n|\r|\v| )*)((\\/\\/[^.](.*))|(\\/\\*(.*?)\\*\\/))";
    commentLineStart = "(\\/\\*)"; // Matches any comment line with // or /*C
    commentLineEnd = "\\*/"; // Matched any ending multicomment line
    blankLine = "(\t|\n|\r|\v| )*"; // Matches blank lines
    trashLines = "(\t|\n|\r|\v| )*(\\{|\\}|\\}\\;)(\t|\n|\r|\v| )*"; //Matches trash lines like { } alone
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
        throw invalid_argument( "Lo sentimos, un archivo no existe, intente de nuevo." );//.m
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
int *Validation::line( string line )//.m
{
    //.d=3
    static int auxArray[2];// 9 is the default value for multilecomments in between.

    //Variable cleaning
    auxArray[0] = 9;
    auxArray[1] = 0;

    if( regex_search( line, tokenB ) ) {

        string auxStoI = "";
        auxArray[0] = 0;

        int pos = 5 + static_cast<int>(line.find("//.b="));

        for (int i = pos; i < line.length(); i++) {
            if(!isspace(line[i]) && line[i] != '\t' && line[i] != '\n') {
                auxStoI += line[i];
            }
        }
        auxArray[1] = stoi(auxStoI);
        return auxArray;
    }

    else if( regex_search( line, tokenD ) ) {
        string auxStoI = "";
        auxArray[0] = 1;

        int pos = 5 + static_cast<int>(line.find("//.d="));

        for (int i = pos; i < line.length(); i++) {
            if(!isspace(line[i]) && line[i] != '\t' && line[i] != '\n') {
                auxStoI += line[i];
            }
        }
        auxArray[1] = stoi(auxStoI);
        return auxArray;
    }

    else if( regex_match( line, tokenM ) ) {
        auxArray[0] = 2;
        for (int i = 0; i < line.length(); i++) {
            if(isspace(line[i]) && line[i] == '\t' && line[i] == '\n' && line[i] == '/') {
                auxArray[1] = 1;
                i += line.length();
            }
        }
        return auxArray;
    }

    else if( regex_search( line, tokenI ) ) { auxArray[0] = 3; return auxArray; }

    else if( regex_search( line, commentSingleLine ) ) { auxArray[0] = 4; return auxArray; }

    else if( regex_search( line, commentLineStart ) ) { auxArray[0] = 5; return auxArray; }

    else if( regex_search( line, commentLineEnd ) ) { auxArray[0] = 6; return auxArray; }

    else if( regex_match( line, blankLine ) ) { auxArray[0] = 7; return auxArray; }

    else if( regex_match( line, trashLines ) ) { auxArray[0] = 8; return auxArray; }

    //.d=15

    return auxArray;//.m
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

/* Returns the name of the string without its extension.
 * Parameters, accepts strign as a parameter
 Returns string
 */
string Validation::nameWithNoExt( string nameExt)
{
    string fileNameNoExt = "";

    for(int i = 0; i <= nameExt.length(); i++)
    {
        if( to_string(nameExt[i]) == "46")
        {
            return fileNameNoExt;
        } else {
            fileNameNoExt += nameExt[i];
        }
    }

    return fileNameNoExt;
}
