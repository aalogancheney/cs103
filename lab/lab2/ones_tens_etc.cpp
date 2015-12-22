#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	// Prompts the user to enter the integer
	cout << "Please enter an integer: ";
	int integer;
	cin >> integer;

	// Initializes a counter to 0. The counter will be used
	// to display the appropriate number when listing the 
	// place of the digit using the pow() function.
	int counter = 0;

	// This loop will continue while the integer is greater
	// than or equal to 10. The moment that it goes below
	// that then execution will exit the loop.
	while(integer / 10) {
		cout << "The " << pow(10, counter) << "'s digit is ";
		int digit = integer % 10;	// We use the same variable for each
		cout << digit << endl;		// digit since each run through the
						// loop clears the variable.
		counter++;	// Increment the counter to go to the next power of 10.
		integer /= 10;	// Update the entered integer to get rid of the used part.
	}

	// These final statements always execute. If the entered integer
	// is less than 10, these statements execute automatically and only display
	// the ones column. Since there is always a leftover digit we need to run
	// these commands at least one time. 
	cout << "The " << pow(10, counter) << "'s digit is ";
	int digit = integer % 10;
	cout << digit << endl;

	return 0;
}
