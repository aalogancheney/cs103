#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

bool coinFlip(double probability);
void takeTurn(int playerCoins[], double probability);

const int NUMBER_OF_PLAYERS = 3;

int main(int argc, char *argv[])
{
	srand(time(0));		// Seed rand().
	cout << "Monte Carlo Simulation: Going Broke" << endl;
	cout << "Please enter the following:" << endl;

	// Prompts for and stores the beginning number of coins for the players.
	cout << "Number of coins each player starts with: ";
	int startingCoins;
	cin >> startingCoins;

	// Prompts for and stores the probability of the coin.
	cout << "Probability of the coin, between 0 and 1: ";
	double probability;
	cin >> probability;

	// Prompts for and stores the number of games to be simulated. 
	cout << "Number of games to simulate: ";
	double numberOfGames;
	cin >> numberOfGames;

	// Declares and initializes a variable to keep track of the number of
	// turns that have passed. This is the only variable we need to keep track
	// of outside of our loops. 
	int totalTurns = 0;

	for(int i = 0; i < numberOfGames; i++) {
		int playerCoins[NUMBER_OF_PLAYERS] = {startingCoins};
		while(playerCoins[0] && playerCoins[1] && playerCoins[2]) {
			takeTurn(playerCoins, probability);
			totalTurns++;
		}
	}

	cout << "For three players playing with " << startingCoins << " coins, a "
	     << probability << " probability of getting heads, and after " 
	     << numberOfGames << " games, we have an average game lasting " 
	     << totalTurns / numberOfGames << " turns." << endl;
	cout << "Thanks for playing!" << endl;

	return 0;
}

bool coinFlip(double probability)
{
	bool result;
	if(static_cast<double>(rand()) / RAND_MAX < probability) {result = true;}
	else {result = false;}
	return result;
}

void takeTurn(int playerCoins[], double probability)
{
	bool playerOneFlip = coinFlip(probability);
	bool playerTwoFlip = coinFlip(probability);
	bool playerThreeFlip = coinFlip(probability);

	if(playerOneFlip && playerTwoFlip && playerThreeFlip) {}
	else if(!(playerOneFlip || playerTwoFlip || playerThreeFlip)) {}
	else if(playerCoins[0] && playerCoins[1]) {
		playerCoins[0] -= 1;
		playerCoins[1] -= 1;
		playerCoins[2] += 2;
	}
	else if(playerCoins[0] && playerCoins[2]) {
		playerCoins[0] -= 1;
		playerCoins[1] += 2;
		playerCoins[2] -= 1;
	}
	else if(playerCoins[1] && playerCoins[2]) {
		playerCoins[0] += 2;
		playerCoins[1] -= 1;
		playerCoins[2] -= 1;
	}
	else if(!(playerCoins[0] || playerCoins[1])) {
		playerCoins[0] -= 1;
		playerCoins[1] -= 1;
		playerCoins[2] += 2;
	}
	else if(!(playerCoins[0] || playerCoins[2])) {
		playerCoins[0] -= 1;
		playerCoins[1] += 2;
		playerCoins[2] -= 1;
	}
	else {
		playerCoins[0] += 2;
		playerCoins[1] -= 1;
		playerCoins[2] -= 1;
	}
	
	return;
}
