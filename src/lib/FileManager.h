    /* Description: Pragrama 1 de Calidad de Software. This class is in charge to manage everything
     * that needs to do with files, opening, closing, reading etc. Also calls validations when needed
     * and handles errores realted to files.
     * Author: Jorge Ivan Diaz Sanchez A01191342
     * Created: Ago-15-2018 , Modified:Sep-15-2018
     */

    // Codigo Base
    //.b=38
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include "Validation.h"

    using namespace std;

    struct StructFile
    {
        // < name, B, D, M, A, T, I >
        string name = "fileName";
        int tokenBase = 0;
        int tokenDelete = 0;
        int tokenModify = 0;
        int tokenAdd = 0;
        int tokenTotal = 0;
        int tokenItem = 0;
    };

    /* FileManager class handles all files like opening a file, keeping the file open
     * close the file, call validations and rhandle file errors
     */
    class FileManager
    {
    public:
        // Constructor
        FileManager();
        // Creates an array of file names
        void fileStorageVector(string);
        // Closees files using fstream from c++
        void close();
        // Gets the name of the file
        string getName();
        // Opens all files for counting
        void readFiles();
        // Prints the expected output
        void printStats();
        // Writes stats to file
        void writeStatsToFile();

    private:
        // Opens files using fstream from c++
        void open( string );//.m
        // Reads files using fstream from c++
        void read( int );//.m
        // Returns the index of the file with no extension
        int fileIndex( string );
        // Returns if file name exists in vFiles
        bool exist( string );

        vector< StructFile > vFiles;//.m
        vector< string > vFilesWithExt;
        fstream  currentFile;
        Validation validate;
        //.d=1
    };

    /* Class constructor
     * Parameters: none
     * Returns: nothing
     */
    FileManager::FileManager() { }

    /* Assigns to vector of file name list using validator returns a void
     * This sets the vector in which stores files and counters for LOC
     * Parameters: accepts a string which contaisn all file names in a single string
     * Returns: void
     */
    void FileManager::fileStorageVector( string fileNames )
    {
        vFilesWithExt = validate.separateFileNames( fileNames );

        //Asigns first element to initiate the vector
        for (int i = 0; i < vFilesWithExt.size(); i++) {
            if ( !this -> exist( vFilesWithExt[i] ) ) {
                vFiles.emplace_back(StructFile{});
                vFiles[i].name = validate.nameWithNoExt(vFilesWithExt[i]);
            }
        }
    }

    /* This opens all files in the vector vFiles and calls counter to coun tokens
     * Parameters: None
     * Returns: void
     */
    void FileManager::readFiles()
    {
        for (int i = 0; i < vFilesWithExt.size(); i++) {
            try {
                this -> open( vFilesWithExt[i] );
                this -> read( fileIndex( vFilesWithExt[i] ) );
                this -> close();
            } catch ( const invalid_argument& e ) {
                 throw e;
            }
        }
    }

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
            //.d
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

    /* this function returns the index of the file in vFiles
     * Parameters: accepts a string to compare with the vFiles vector
     * Returns int which is the index
     */
    int FileManager::fileIndex( string fileName)
    {
        for (int i = 0; i < vFiles.size(); i++) {

            if (vFiles[i].name == validate.nameWithNoExt( fileName )) {
                return i;
            }
        }

        return 0;//If not found it returns 0 as index, means it was the first element
    }

    /* This functions returns true or fales if file exists or not
     * Parameters: String of name of file
     * Returns boolean true if exists fale if not
     */
    bool FileManager::exist( string fileName )
    {
        for (int i = 0; i < vFiles.size(); i++) {

            if (vFiles[i].name == validate.nameWithNoExt( fileName )) {
                return true;
            }
        }

        return false;
    }


    /* This function prints all the stats gathered from reading the files
     * Parameters: none
     * Returns: void
     */
    void FileManager::printStats()
    {
        int auxCounter = 0;// Array to add all necessary counters: / [ B, D, M, A, T, I ]
        /*
         * Tipo de parte / Criterio
         * BASE B>0 y (M>0 o D>0 o A>0)
         * NUEVA B=0 y M=0 y D=0 y A>0
         * REUSADA B>0 y M=0 y D=0 y A=0
        */

        // ========= Partes Base ====================
        cout << "PARTES BASE:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase > 0 && ( vFiles[i].tokenModify > 0 || vFiles[i].tokenDelete > 0 || vFiles[i].tokenAdd > 0 )) {
                cout << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << ", B=" << vFiles[i].tokenBase
                << ", D=" << vFiles[i].tokenDelete
                << ", M=" << vFiles[i].tokenModify
                << ", A=" << vFiles[i].tokenAdd
                << endl;
            }
        }
        cout << "--------------------------------------------" << endl;

        // ========= Partes Nuevas ==================
        cout << "PARTES NUEVAS:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase == 0 && vFiles[i].tokenModify == 0 && vFiles[i].tokenDelete == 0 && vFiles[i].tokenAdd > 0 ) {
                cout << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << endl;
            }
        }
        cout << "--------------------------------------------" << endl;

        // ========= Partes Reusadas ================
        cout << "PARTES REUSADAS:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase > 0 && vFiles[i].tokenModify == 0 && vFiles[i].tokenDelete == 0 && vFiles[i].tokenAdd == 0 ) {
                cout << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << ", B=" << vFiles[i].tokenBase
                << endl;
            }
        }
        cout << "--------------------------------------------" << endl;

        // ============= Total ======================
        cout << "Total de LDC=";
        for (int i = 0; i < vFiles.size(); i++) {
            auxCounter += vFiles[i].tokenTotal;
        }
        cout << auxCounter << endl;
    }

    /* This function writes all the stats gathered from reading the files into a file names 'ConteoLDC.txt'
     * Parameters: none
     * Returns: void
     */
    void FileManager::writeStatsToFile()
    {
        ofstream conteoLDC;

        conteoLDC.open("ConteoLDC.txt");

        int auxCounter = 0;// Array to add all necessary counters: / [ B, D, M, A, T, I ]
        /*
         * Tipo de parte / Criterio
         * BASE B>0 y (M>0 o D>0 o A>0)
         * NUEVA B=0 y M=0 y D=0 y A>0
         * REUSADA B>0 y M=0 y D=0 y A=0
         */

        // ========= Partes Base ====================
        conteoLDC << "PARTES BASE:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase > 0 && ( vFiles[i].tokenModify > 0 || vFiles[i].tokenDelete > 0 || vFiles[i].tokenAdd > 0 )) {
                conteoLDC << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << ", B=" << vFiles[i].tokenBase
                << ", D=" << vFiles[i].tokenDelete
                << ", M=" << vFiles[i].tokenModify
                << ", A=" << vFiles[i].tokenAdd
                << endl;
            }
        }
        conteoLDC << "--------------------------------------------" << endl;

        // ========= Partes Nuevas ==================
        conteoLDC << "PARTES NUEVAS:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase == 0 && vFiles[i].tokenModify == 0 && vFiles[i].tokenDelete == 0 && vFiles[i].tokenAdd > 0 ) {
                conteoLDC << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << endl;
            }
        }
        conteoLDC << "--------------------------------------------" << endl;

        // ========= Partes Reusadas ================
        conteoLDC << "PARTES REUSADAS:" << endl;
        for (int i = 0; i < vFiles.size(); i++) {
            if ( vFiles[i].tokenBase > 0 && vFiles[i].tokenModify == 0 && vFiles[i].tokenDelete == 0 && vFiles[i].tokenAdd == 0 ) {
                conteoLDC << vFiles[i].name
                << ": T=" << vFiles[i].tokenTotal
                << ", I=" << vFiles[i].tokenItem
                << ", B=" << vFiles[i].tokenBase
                << endl;
            }
        }
        conteoLDC << "--------------------------------------------" << endl;

        // ============= Total ======================
        conteoLDC << "Total de LDC=";
        for (int i = 0; i < vFiles.size(); i++) {
            auxCounter += vFiles[i].tokenTotal;
        }
        conteoLDC << auxCounter << endl;
    }

    /* Reads line by line the opened file for validation and counting lines of code, blank, comments
     * Parameters: int array counter[4] will be the array that contains the counters of the
     * blank, comment and code lines
     * Returns: void
     */
    void FileManager::read( int index )//.m
    {
        string line;
        int *auxArray;
        int auxCounter = 0;// Counts unnecessary lines such as comments, blanks etc, the rest is the lines of code
        bool flagMultiCommentLine = false;

        try
        {
            while ( !currentFile.eof() )
            {
                vFiles[index].tokenTotal++;//Adds total lines

                getline( currentFile, line );

                auxArray = validate.line( line );

                // < B, D, M, A, T, I >
                switch( auxArray[0] )
                {
                    case 0:
                       auxCounter++;// Token Base
                        vFiles[index].tokenBase += auxArray[1];
                        break;
                    case 1:
                        auxCounter++;// Token Deleted
                        vFiles[index].tokenDelete += auxArray[1];
                        break;
                    case 2:
                        // Token Modified
                        if( flagMultiCommentLine ) {
                            auxCounter++;
                        } else {
                            //Increment Modified
                            if ( auxArray[1] != 0 ) {
                                auxCounter++;
                            }
                            vFiles[index].tokenModify++;
                        }
                        break;
                    case 3:
                        auxCounter++;// Token Item
                        vFiles[index].tokenItem++;
                        break;
                    case 4:
                        auxCounter++;//Single Comment
                        break;
                    case 5:
                        auxCounter++;//MultiComment Start
                        flagMultiCommentLine = true;
                        break;
                    case 6:
                        auxCounter++;//MultiComment End
                        flagMultiCommentLine = false;
                        break;
                    case 7:
                        auxCounter++;//Blank Line
                        break;
                    case 8:
                        auxCounter++;//Trash Line
                        break;
                    case 9:
                        if( flagMultiCommentLine ) { auxCounter++; }//MultiComment lines in between
                        break;
                    default:
                        break;
                }
            }

            //cout << "TOTAL: " << vFiles[index].tokenTotal << "  , AuxCounter: " << auxCounter << endl;
            vFiles[index].tokenTotal -= auxCounter;//Substracts trash lines

            // A = T - B + D
            vFiles[index].tokenAdd += vFiles[index].tokenTotal - vFiles[index].tokenBase + vFiles[index].tokenDelete;
            //.d=1

        }
        catch ( const invalid_argument& e )
        {
            throw e;
        }
    }

    //.d=2
