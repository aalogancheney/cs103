#include <iostream>
#include <cstring>

using namespace std;

const int ARRAY_SIZE =80;

int main(int argc, char *argv[]) {

    char myString[ARRAY_SIZE] = "ComputerScience";
    char yourString[ARRAY_SIZE];
    char *aString; 

    // yourString = myString;

    strncpy(aString, myString, ARRAY_SIZE);

    aString = myString;
    strncpy(yourString, myString, ARRAY_SIZE);

    cout << "Here is the original string: " << aString << endl;
    cout << "Here is your string: " << yourString << endl;

    myString[0] = '*';
    
    cout << "Here is the original string now: " << aString << endl;
    cout << "Here is your string now: " << yourString << endl;

    return 0;
}
