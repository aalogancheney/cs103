// hangman.cpp

// This exercise will illustrate the string library functions, character arrays,
// arrays of pointers, etc. 

// The program must include the following:
//  1. Select a word at random from the array wordBank.
//  2. Display the secret word every turn, blocking out any unknown letters with
//     *'s and showing any correctly guessed letters in their correct places. 
//  3. The user should have 10 lives, and each incorrect guess takes away a life.
//     Correct guesses do not subtract a life (what if the word had more than 10 
//     letters?
//  4. We have to use strlen() and strcmp() in our program from the cstring library. 
//  5. We must complete and use the function processGuess() (i.e. we cannot make 
//     our own function and use that.) The function should take three arguments:
//     the value of the current word guessed so far, the secret word, and the
//     current letter guessed. The function should return the value of the number
//     of times the letter appears in the secret word, thus if the return value is
//     0, the player guessed incorrectly and we can decrement the number of lives the
//     player has. The function should also change the appropriate letters in the 
//     guessed word from *'s to the actual letters. 
//  6. On every turn we should display the number of turns left and the word as it
//     currently stands. 
//  7. The end of the game should show a description to the user that tells them 
//     whether they won or lost. 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype for the function processGuess(). It has three formal arguments: the
// word as it stands based on what letters the player has guessed, the actual
// target word, and the letter that the user guessed. The function returns an integer
// value which tells the calling function how many of the guessed letters appear in
// the target word. If 0, the player did not guess a letter correctly, otherwise they
// guessed a letter that is in the word.
int processGuess(char* word, const char* targetWord, char guess);

// This defines an array of char *, which has 10 words that can be picked at random.
// Recall that a char * points to a character, and that an array name is already a 
// pointer to the first element in that array. So here we actually do want an array 
// of char *. 
const char *wordBank[] = {"computer",
                          "president",
                          "trojan",
                          "program",
                          "coffee",
                          "library",
                          "football",
                          "popcorn",
                          "science",
                          "engineer"};

// The number of words contained in the array wordBank. 
const int numWords = 10;

int main() {

    // Seeds the random function based on the time. Recall this only needs to be called
    // once so it is put at the beginning of main().
    srand(time(0));
    // Declares a variable guess of type char. 
    char guess;
    // Declares a variable wordGuessed of type bool and initializes it to false. The 
    // reason for this is because the player has not guessed the word from the beginning. 
    bool wordGuessed = false;
    // Declares a variable numTurns of type int to signify the number of turns a player
    // has to guess a word.
    int numTurns = 10;

    // This declares and initializes the variable targetWord using the random function
    // to pick a word from the predefined wordBank array. 
    const char* targetWord = wordBank[rand() % 10];

    char word[80];  

    // Initializes the array word to all *'s
    for (int i = 0; i < 80; i++) {
        word[i] = '*';
    }
    
    // Finds the end of the string of the targetWord and sets that value in the array
    // word to the null character, so that when we are displaying the array word we
    // don't see all 80 values. 
    size_t terminatingPosition = strlen(targetWord);
    word[terminatingPosition] = '\0';
    
    while(numTurns > 0 && !wordGuessed) {
        cout << "Current word: " << word << endl;
        cout << "Turns remaining: " << numTurns << endl;
        cout << targetWord << endl;
        cout << "Enter a letter to guess: ";
        cin >> guess;
        
        int correctLetters = processGuess(word, targetWord, guess);

        if(!correctLetters) {
            numTurns--;
        }

        if(!strcmp(word, targetWord)) {
            wordGuessed = true;
        }
    }

    if (wordGuessed) {
        cout << "The word was: " << targetWord << ". You win!" << endl;
    }
    else {
        cout << "You didn't guess the word in enough time. You lose." << endl;
    }
    
    return 0;
}

int processGuess(char* word, const char* targetWord, char guess) {
    int numberOfCorrectLetters = 0;

    for(size_t i = 0; i < strlen(targetWord); i++) {
        if(*(targetWord + i) == guess) {
            *(word + i) = guess;
            numberOfCorrectLetters++;
        }
    }
    
    return numberOfCorrectLetters;
}

