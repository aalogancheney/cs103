#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bmplib3.h"
#include "turtle.h"

using namespace std; 

// Creates an array of color variables which stores the pre-defined 
// variables for colors as defined in the bmplib3.h file. This way, we
// can access them as needed. (I have left out black, since it won't draw
// well.)
const color colorChoices[10] = {red, blue, green, yellow, cyan, magenta, 
                                white, gray, orange, purple};
             
// This function will randomize the color of the turtles in our 
// dynamically allocated array.                    
void randomizeColors(Turtle *turtles, int numberOfturtles);

int main(int argc, char* argv[]) {
  // Seeds the time according to the time at run-time. This means we will have
  // random colors all the time. 
  srand(time(0));
  cout << "Enter the number of turtles you want to draw: ";
  int numberOfTurtles;
  cin >> numberOfTurtles;
  
  // Dynamically allocates an array of Turtle objects based on the inforamtion
  // set by the user. 
  Turtle *turtles = new Turtle[numberOfTurtles];
  
  // Will initially randomize the colors that are going to be drawn. 
  randomizeColors(turtles, numberOfTurtles);
  
  for(int i = 0; i < numberOfTurtles; i++) {
    turtles[i].turn(i * 360 / numberOfTurtles);
    turtles[i].move(SIZE/4);
  }
  
  // Shows the drawing. 
  std_show();
  
  // Deletes the dynamically allocated array of Turtle objects.
  delete [] turtles;
  return 0;
}

void randomizeColors(Turtle *turtles, int numberOfTurtles) {
  for(int i = 0; i < numberOfTurtles; i++) {
    turtles[i].setColor(colorChoices[rand() % 10]);
  }
}

/*void fractal(int counter, int numberOfTurtles, Turtle *previousTurtles) {
  if(counter == 0) {
    return;
  } else {
    Turtle *newTurtles = new Turtle[numberOfTurtles];
    for(int i = 0; i < numberOfTurtles; i = i + 2) {
      newTurtles[i] = previousTurtles[i];
      newTurtles[i + 1] = previousTurtles[i];
    }
  }
}*/
