// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
// arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

// Using declarations for each of the objects in the std namespace
// used in this program.
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

// Prototype for the permute() function, which takes two arguments, an
// array of char, and the length of that array of char. 
void permute(char items[], int len);

// This is the maximum word length we expect to encounter. 
const int MAX_WORD = 41;

// Formal arguments were added to the main() function so that we can use
// command line arguments to read from a file. 
int main(int argc, char* argv[])
{
  // Checks to see if there are the appropriate number of command line
  // arguments given to the program.
  if(argc < 2) {
    cout << "Enter two command line arguments: the name of the program and\n"
         << "the name of a text file to be read." << endl;
    return 1;
  }

  // declares an ifstream variable called ifile and associates that 
  // ifstream variable with the file provided as the second command line
  // argument. The if condition checks to make sure the file was
  // successfully opened. 
  ifstream ifile(*(argv + 1));
  if(ifile.fail()) {
    cout << "Could not open file " << *(argv + 1) << ", now quiting." << endl;
    return 1;
  }

  // Declares the number of words to be allocated later. The ifile variable 
  // is used in place of cin and it reads directly from the file. If there
  // is not a number at the beginning of the file, the program exits. 
  int numberOfWords;
  ifile >> numberOfWords;
  if(ifile.fail()) {
    cout << "Could not read the first value from " 
         << *(argv + 1) << ", now quiting." << endl;
    return 1;
  }

  // Dynamically allocates an array of char* of size numberOfWords as 
  // entered from the beginning of the file. Each element of the array
  // is itself a char* since each element is a string of characters, 
  // therefore the return type is char** (this tripped me up at first).
  char **wordBank = new char*[numberOfWords];
  char buffer[MAX_WORD];

  // Iterates through the words in the file and creates a deep copy of
  // the information. First, we use ifile to read a word into our buffer
  // array (since the >> operator skips over whitespace). Then we 
  // check how long that word is using strlen() (recall that this does
  // not include the null character when finding the length). Then we
  // assign each element of the array wordBank a dynamically allocated
  // array of char (this works since each element of wordBank is a char*
  // and the return type from the new declaration is char *). We add one
  // to account for the null character. Finally, we use strcpy to copy
  // the information from the buffer array into the new array in the 
  // wordBank array. Recall that strcpy() will copy the null character
  // IF there is room, which we have ensured through our use of 
  // strlen().
  for(int i = 0; i < numberOfWords; i++) {
    ifile >> buffer;
    int stringLength = strlen(buffer);
    wordBank[i] = new char[stringLength + 1];
    strcpy(wordBank[i], buffer);
  }
  
  // Seeds time and allocates space for a guess.
  srand(time(0));
  char guess[80];
  
  // Initializes the guess to false and sets the number of turns to 10.
  bool wordGuessed = false;
  int numTurns = 10;

  // Picks a random word from the wordBank array and gets the length of
  // that word, since each word has its own length and we need to know
  // that length in order to scramble the word properly and terminate
  // it with a null character. 
  int target = rand() % numberOfWords;
  int targetLen = strlen(wordBank[target]);

  // Initialization of the permuted word.
  char *word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // The game continues while the word has not been guessed and while the
  // player still has turns left. The scrambled word is shown to the player
  // and they are given the opportunity to guess. If the word is guessed,
  // we use some clever boolean operations to assign the wordGuessed variable
  // a zero value only when the player guesses the word. 
  while(!wordGuessed && numTurns > 0) {
    cout << "\nCurrent word:  " << word << endl;
    cin >> guess;
    wordGuessed = (strncmp(guess, wordBank[target], targetLen + 1) == 0);
    numTurns--;
  }
  
  // The message shows to the player if they win, and otherwise tells them
  // they took too many turns. 
  if(wordGuessed) {
    cout << "You win!" << endl;
  } else {
    cout << "Too many turns...You lose!" << endl;
  }

  // Deletes the information allocated for the scrambled word. 
  delete [] word;

  // Deletes the information that the array wordBank points to. These are
  // the individual elements within the wordBank array.
  for(int i = 0; i < numberOfWords; i++) {
    delete [] *(wordBank + i);
  }

  // This final delete statements deletes the space that the wordBank
  // array itself takes up. Each element takes up space, and the array
  // itself takes up space. 
  delete [] wordBank;

  // Closes the file we associated with the ifile variable. 
  ifile.close();

  return 0;
}

// This function scrambles the letters using the rand() function.
void permute(char items[], int len)
{
  for(int i = len - 1; i > 0; --i) {
    int r =  rand() % i;
    int temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
  
  return;
}

