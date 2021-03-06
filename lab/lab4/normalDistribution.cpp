#include <iostream>
#include <ctime>	// We use srand()
#include <cstdlib>	// We use rand()
#include <iomanip>	// We use setw() to make our output uniform

using namespace std;

// Function prototypes for our two functions. The first generates a random number
// and returns that number, and the second prints the contents of an array.
int roll(void);
void printHistogram(int counts[]);

// My program allows the manipulation of the number of dice used in the experiment. If
// that number is set ahead of time, everything else falls into place. The second constant
// used here is dependent only on the number of dice and relies on mathematical
// properties of dice to calculate how many possible values there are.
const int NUMBER_OF_DICE = 7;
const int NUMBER_OF_SIDES = 10;
const int POSSIBLE_VALUES = NUMBER_OF_SIDES * NUMBER_OF_DICE - NUMBER_OF_DICE + 1;

int main(int argc, char *argv[])
{
	// Seeds the rand() function. I made the mistake of seeding the rand() function
	// in roll() initially, and I was getting the same value for each roll of the 
	// dice. This is because the internal clock runs at such high speeds that there
	// was no time between calculations for rand() to change.
	srand(time(0));

	cout << "We will be rolling " << NUMBER_OF_DICE << " " << NUMBER_OF_SIDES 
	     << "-sided dice and testing the normal distribution." << endl;
	cout << "Enter q to quit." << endl;

	int numberOfExperiments;
	cout << "Please enter the number of experiments you want to run: ";

	// This while loop will execute so long as cin is not flagged. We also use the 
	// while loop to get input from the user.
	while(cin >> numberOfExperiments) {
		// The size of this array is known at compile-time, but we can easily change
		// its size based on the number of dice we use in the experiment.
		int results[POSSIBLE_VALUES] = {0};

		// The first loop runs through the number of experiments, as set by the user.
		for(int i = 0; i < numberOfExperiments; i++) {
			// The runningSum variable is declared inside this loop so that after 
			// each experiment is finished, the variable is thrown away and a new 
			// one is initialized at 0.
			int runningSum = 0;
			// The inner for loop executes based on the number of dice there are 
			// in the experiment. The runningSum variable is incremented by the 
			// appropriate value as determined by the roll() function.
			for(int j = 0; j < NUMBER_OF_DICE; j++) {
				runningSum += roll();
			}
			// After each experiment is run, we place the total in the array. 
			// Notice that we have to subtract NUMBER_OF_DICE in order to fill the 
			// appropriate array elements, since indexing starts at 0. This way, 
			// we are sure to cover the entire range of values as given by 
			// POSSIBLE_VALUES.
			results[runningSum - NUMBER_OF_DICE]++;
		}

		// Shows the results to the user.
		printHistogram(results);

		cout << "Please enter the number of experiments you want to run: ";
	}

	cout << "Thanks for playing!" << endl;

	return 0;
}

int roll(void)
{
	// We use mod NUMBER_OF_SIDES because we define at the top of the program
	// the number of sides on a dice. 
	int random = rand() % NUMBER_OF_SIDES + 1;
	return random;
}

void printHistogram(int counts[])
{
	// The first loop runs over the possible values of our experiment, which is
	// also the size of the array.
	for(int i = 0; i < POSSIBLE_VALUES; i++) {
		// Here setw() formats the output so everything prints nicely
		cout << setw(2) << i + NUMBER_OF_DICE << ": ";
		// The inner for loop prints X so long as j increments to the value at that 
		// location in the array 
		for(int j = 0; j < counts[i]; j++) {
			cout << "X";
		}
		cout << endl;
	}
}
