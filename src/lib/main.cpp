/* Description: Pragrama 1 de Calidad de Software. This program is for Software Quality
 * It is the first program of the semester. Its purpose is to count how many blank lines, comment
 * lines and coding lines there are in a functional code, displaying the results
 * Author: Jorge Ivan Diaz Sanchez A01191342
 * Created: Ago-15-2018 , Modified:Ago-20-2018
 */

#include <iostream>
#include <string>
#include "FileManager.h"

using namespace::std;

/* This main function is in charge of managing the inputs and outputs for the user.
 * Parameters: none
 * Returns 0
 */

int main() {

  int counters[4] = { 0, 0, 0, 0 };
  string fileName;
  FileManager file;

  cout << "Insert file name with extension: ";
  cin >> fileName;;

  try
  {
    file.open( fileName );
    file.read( counters );

    cout << "Nombre del archivo: " << file.getName() << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Cantidad de líneas en blanco: " << counters[0] << endl;
    cout << "Cantidad de líneas con comentarios: " << counters[1] << endl;
    cout << "Cantidad de líneas con código " << counters[2] << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Numero total de lineas: " << (counters[3]) << endl;

  }
  catch ( const invalid_argument& e )
  {
    cerr << "exception: " << e.what() << endl;
  }

  try
  {
    file.close();
  }
  catch ( const invalid_argument& e )
  {
    cerr << "exception: " << e.what() << endl;
  }

  return 0;
}
