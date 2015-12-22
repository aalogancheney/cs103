#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(0));
	
	int secretNumber = rand() % 20;
	int numberOfGuesses = 5;
	int guess;

	while( numberOfGuesses-- > 0) {
		cout << "Enter a number: " << endl;
		cin >> guess;
		if( guess == secretNumber ) {
			cout << "You win!!" << endl;
			break;
		}
		else if( guess > secretNumber ) {
			cout << "Guess lower" << endl;
		}
		else {
			cout << "Guess higher" << endl;
		}
	}

	if( numberOfGuesses == 0) {
		cout << "You lose!!" << endl;
	}

	return 0;
}
