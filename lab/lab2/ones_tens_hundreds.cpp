#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Enter an integer between 0 and 999: ";
	int integer;
	cin >> integer;

	int ones = integer % 10;
	integer /= 10;
	int tens = integer % 10;
	integer /= 10;
	int hundreds = integer % 10;

	cout << "The 1's digit is " << ones << endl;
	cout << "The 10's digit is " << tens << endl;
	cout << "The 100's digit is " << hundreds << endl;

	return 0;
}
