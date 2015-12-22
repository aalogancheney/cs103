#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream file(argv[1]);
  
  if(argc < 2) {
    cout << "Please provide a file name." << endl;
    return 1;
  } else if(file.fail()) {
    cout << "Could not open the file " << argv[1] << "." << endl;
    return 1;
  }
  
  string name;
  string tempName;
  file >> name;
  double sales = 0;
  double tempSales;
  file >> tempSales;
  sales += tempSales;
  
  while(file >> tempName >> tempSales) {
    if(tempName == name) {
      sales += tempSales;
    } else {
      cout << name << ": " << sales << endl;
      name = tempName;
      sales = tempSales;
    }
  }
  
  cout << name << ": " << sales << endl;
  file.close();
 
  return 0;
}
