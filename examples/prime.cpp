#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Please enter a number. We will check if it is prime: ";
	int test;
	cin >> test;

	int counter = 2;

	while( test % counter != 0 ) {
		counter++;
	}

	if(counter == test) {
		cout << test << " is prime." << endl;
	}
	else {
		cout << test << " is not prime because " << counter << " divides"
		     << " into " << test << endl;
	}

	return 0;
}
