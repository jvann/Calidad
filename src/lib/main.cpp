/* Description: Pragrama 1 de Calidad de Software. This program is for Software Quality
 * It is the first program of the semester. Its purpose is to count how many blank lines, comment
 * lines and coding lines there are in a functional code, displaying the results
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Ago-20-2018
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
  int counters[4] = { 0, 0, 0, 0 };
  string fileNames;//.m
  FileManager fileManager;

  cout << "Insert file names with extension: ";//.m

  getline( cin, fileNames);//.m

  try
  {
    fileManager.fileStorageVector(fileNames);
    //file.open( fileName );
    //file.read( counters );
    cout << "PARTES BASE:" << endl;
    cout << "Lista: T=" << "Counter here" << ", I=" << "Counter here" << ", B=" << "Counter here" << ", D=" << "Counter here" << ", M=" << "Counter here" << ", A=" << "Counter here" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "PARTES NUEVAS:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "PARTES REUSADAS:" << endl;
    cout << "Nodo: T=27, I=1, B=27" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Total de LDC=69" << endl;
    /* cout << "Nombre del archivo: " << file.getName() << endl;
    cout << "--------------------------------------------" << endl;//.m
    cout << "Cantidad de líneas en blanco: " << counters[0] << endl;//.
    cout << "Cantidad de líneas con comentarios: " << counters[1] << endl;
    cout << "Cantidad de líneas con código " << counters[3] - (counters[0] + counters[1]) << endl;//.m
    cout << "--------------------------------------------" << endl;
    cout << "Numero total de lineas: " << counters[3] << endl;
*/
  }
  catch ( const invalid_argument& e )
  {
    cerr << "exception: " << e.what() << endl;
  }

  try
  {
    //fileManager.close();
  }
  catch ( const invalid_argument& e )
  {
    cerr << "exception: " << e.what() << endl;
  }

  return 0;
}
