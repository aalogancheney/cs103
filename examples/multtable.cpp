#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Please enter the first bound for the multiplication table: ";
	int first;
	cin >> first;
	cout << "Please enter the second bound for the multiplication table: ";
	int second;
	cin >> second;

	for(int row = 1; row <= first; row++) {
		for(int column = 1; column <= second; column++) {
			cout << left << setw(5) << row * column;
		}
		cout << endl;
	}

	// cout << RAND_MAX; 

	return 0;
}
