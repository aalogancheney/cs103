#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	// Prompts the user for an integer number.
	cout << "Please enter a positive integer number: ";
	int integer;
	cin >> integer;

	// Initializes three variables: two of them are counters that will
	// increment for each factor of 2 or 3 that is found; the other 
	// variable is a copy of the input value, which means the program
	// can constantly access the original value while manipulating the
	// copy.
	int twosCounter = 0;
	int threesCounter = 0;
	int integerCopy = integer;

	// As long as the integer is positive and greater than 1, the loop
	// will execute. This takes care of the case that the user enters a
	// negative number or 0 or 1. 
	while(integerCopy > 1)
	{
		// Checks that the integer is divisible by 2.
		if(integerCopy % 2 == 0)
		{
			// Increments the twos counter and updates the copy
			twosCounter++;
			integerCopy /= 2;
		}
		// Checks that the integer is divisible by 3.
		else if(integerCopy % 3 == 0)
		{
			// Increments the threes counter and updates the copy
			threesCounter++;
			integerCopy /= 3;
		}
		// If the number passed the first while loop test, but it does not
		// have a divisor of 2 or 3 the if statement will redirect here,
		// showing the user the result, and then changing the copy to
		// 0, which will cause the while loop to terminate. 
		else
		{
			cout << endl << integer << " does not have prime factors" << endl;
			cout << "consisting of only 2 and 3." << endl << endl;
			integerCopy = 0;
		}
	}

	// If the integer reached its goal of 1, then this will show the correct
	// output. If not, this whole thing will never show.
	if(integerCopy != 0)
	{
		cout << endl << integer << " has " << twosCounter 
		     << " factor(s) of two and" << endl;
		cout << threesCounter << " factor(s) of three." << endl << endl;
	}

	// Final message to user. 
	cout << "Thanks for playing!" << endl;

	return 0;
}

