/*
    Aaron Cheney | acheney@usc.edu
    This program runs a Monte Carlo simulation for the Going Broke game. Three
    players flip coins at the same time, and the person who flips the "odd" coin
    gets to take the other two player's coins. The game ends when one of the 
    three players no longer has any coins left.
*/

#include <iostream>
#include <ctime>    // Since we use time().
#include <cstdlib>    // Since we use rand() and RAND_MAX.
#include <iomanip>    // Included for debugging purposes, such as boolalpha.

using namespace std;

// Using a const int gets rid of "magic" numbers showing up in the program. 
const int NUMBER_OF_PLAYERS = 3;

// This function has a formal argument of type double and will return a type bool. 
// The function simulates a coin toss and will return true or false depending on 
// the probability of the coin. The function assumes the user enters a probability
// between 0 and 1.
bool flip(double probability);

int main(int argc, char *argv[])
{
    // We only need to seed rand() once, so it is done at the beginning of main().
    srand(time(0));

    // The following lines prompt the user to enter the information into the 
    // program.
    cout << "Monte Carlo Simulation: Going Broke" << endl;

    cout << "Enter the number of coins each player starts with: ";
    int numberOfCoins;
    cin >> numberOfCoins;

    cout << "Enter the fairness of the coin: ";
    double probability;
    cin >> probability;
    
    cout << "Enter the number of simulations you want to run: ";
    // Notice that we don't have to make this number a double -- there will never be
    // a fractional number of simulations -- but the reason we use a double here is 
    // so that later when we divide totalTurns / simulations, the / operator is the
    // floating-point division, not integer division. 
    double simulations;
    cin >> simulations;

    // Declares a counter for the number of turns. This is the ONLY variable that 
    // needs to be known once the simulations are over, and therefore it is declared
    // outside of the loops. 
    int totalTurns = 0;
    
    // This while loop checks to see if the cin object has been flagged by a type
    // mis-match. If it has, then the program exits the while loop, which will then
    // terminate the program. 
    while(!cin.fail()) {

        // This for loop runs over the total number of simulations, as chosen by
        // the user. 
        for(int i = 0; i < simulations; i++) {

            // Declares an array of the size NUMBER_OF_PLAYERS to hold the 
            // number of coins each players holds. 
            int coins[NUMBER_OF_PLAYERS];

            // Fills the array coins[], with size NUMBER_OF_PLAYERS, with the value
            // numberOfCoins.
            fill_n(coins, NUMBER_OF_PLAYERS, numberOfCoins);

            // This while loop will continue so long as every player has at least
            // one coin. Since the time this will take is unknown, we use a while
            // loop instead of a for loop. 
            while(coins[0] && coins[1] && coins[2]) {

                // Declares and initializes an array flips[] of size 
                // NUMBER_OF_PLAYERS to different random coin flips based on
                // the probability entered by the user. 
                bool flips[NUMBER_OF_PLAYERS] = {flip(probability), 
                                 flip(probability),
                                 flip(probability)};
    
                // This if else branch checks all 8 cases that can occur, 
                // starting first with the two cases where all coins are the 
                // same. The reason for starting with these two cases is that
                // the later cases are subcases, and if we don't check 
                // these first we may increment and decrement the values 
                // incorrectly.  
                if(flips[0] && flips[1] && flips[2]) {    
                    // Empty braces take no action.
                }
                else if(!(flips[0] || flips[1] || flips[2])) {
                }
                // This checks the case that players one and two both have the 
                // same flip, which means player three has the unique flip. 
                // We know this has to be the case since we have already checked 
                // the possibility that player three also has the same coin 
                // flip. This check case and the next two cases use the AND 
                // method to look for differences. 
                else if(flips[0] && flips[1]) {
                    coins[0] -= 1;
                    coins[1] -= 1;
                    coins[2] += 2;    
                }
                // Checks if player two has the unique flip. 
                else if(flips[0] && flips[2]) {
                    coins[0] -= 1;
                    coins[1] += 2;
                    coins[2] -= 1;
                }
                // Checks if player one has the unique flip.
                else if(flips[1] && flips[2]) {
                    coins[0] += 2;
                    coins[1] -= 1;
                    coins[2] -= 1;
                }
                // This checks the case that player three has the unique flip, 
                // but this time we use the OR operator, which checks the 
                // other half of the possibilities. This check case and the 
                // next two cases use the OR method to check for differences. 
                else if(!(flips[0] || flips[1])) {
                    coins[0] -= 1;
                    coins[1] -= 1;
                    coins[2] += 2;
                }
                // Checks if player two has the unique flip.
                else if(!(flips[0] || flips[2])) {
                    coins[0] -= 1;
                    coins[1] += 2;
                    coins[2] -= 1;
                }
                // Checks if player one has the unique flip. 
                else {
                    coins[0] += 2;
                    coins[1] -= 1;
                    coins[2] -= 1;
                }

                // Every time through the while loop, this is incremented to 
                // signify that a turn has taken place. 
                totalTurns++;
            }
        }

        // Shows the user the results of the experimentation. Notice that we don't 
        // need to do a static_cast typecast to get the appropriate output, 
        // since the variable simulations is already of type double. 
        cout << "The average game with the given conditions takes " 
                  << totalTurns / simulations << " turns." << endl << endl;
        
        // Starts a new simulation of the game and shows the users the prompts 
        // again. However, we do not re-declare the variables, instead we just 
        // ask the user to enter the information again and we reset the number 
        // of turns to 0.     
        cout << "Starting a new simulation... Press \"q\" to exit." << endl;
        
        cout << "Enter the number of coins each player starts with: ";
        cin >> numberOfCoins;

        cout << "Enter the fairness of the coin: ";
        cin >> probability;
    
        cout << "Enter the number of simulations you want to run: ";
        cin >> simulations;

        totalTurns = 0;
    }

    cout << endl << "Thanks for playing!" << endl;

    return 0;
}

bool flip(double probability)
{
    // Declare a variable result so that we only have one return statement
    // in the function. 
    bool result;

    // Here we do need a static_cast to keep the decimal part from the division by
    // RAND_MAX. This division will normalize the randomness to fall between 
    // 0 and 1.
    double flip = static_cast<double>(rand()) / RAND_MAX;

    // This if else branch uses the user-entered probability to decide which 
    // result to return. It doesn't matter which value corresponds to heads or 
    // tails, since there is symmetry around the case where probability = 0.5. 
    if(flip < probability) {
        result = true;
    }
    else {
        result = false;
    }

    return result; 
}
