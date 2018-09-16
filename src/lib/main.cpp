/* Description: Pragrama 1 de Calidad de Software. This program is for Software Quality
 * It is the first program of the semester. Its purpose is to count how many blank lines, comment
 * lines and coding lines there are in a functional code, displaying the results
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Sep-15-2018
 */

// Codigo Base
//.b=27
#include <iostream>
#include <string>
#include <vector>
#include "FileManager.h"

using namespace::std;

/* This main function is in charge of managing the inputs and outputs for the user.
 * Parameters: none
 * Returns 0
 */

int main() {

    //blanks, comments, code, total
    string fileNames;//.m
    FileManager fileManager;

    cout << "Insert file names with extension: ";//.m

    getline( cin, fileNames);//.m

    try
    {
        fileManager.fileStorageVector(fileNames);
        fileManager.readFiles();
        fileManager.printStats();
        fileManager.writeStatsToFile();

        //.d=9
    }
    catch ( const invalid_argument& e )
    {
        cerr << "exception: " << e.what() << endl;
    }

    //.d=4

    return 0;
}

