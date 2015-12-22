#include <iostream>
#include <fstream>  // Included to use ifstream and ofstream.

using namespace std;

int main(int argc, char *argv[])
{
  // ifstream is a variable type, so we can create variables with any name of
  // this type. Then we have to give the file name attached to the variable
  // ifile. 
  ifstream ifile(*(argv + 1));
  if(ifile.fail()) {
    cout << "Could not read the file " << *(argv + 1) << endl;
  }
  ofstream ofile(*(argv + 2));
  int x, sum = 0;   // These variables store information from the file to the RAM.

  while(ifile >> x) {
    sum += x;
  }
  
  if(!ifile.fail()) {
    ofile << "sum = " << sum << endl;
  }
  
  ifile.close();  // We should close file streams when we are finished with them. 
  ofile.close();

  return 0;
}
