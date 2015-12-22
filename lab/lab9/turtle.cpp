#include <cmath>
#include "turtle.h"
#include "bmplib3.h"

// This default constructor will start the turtle at the middle of the screen,
// with a downward direction, the color red, and the turtle will be drawn.
Turtle::Turtle() {
  currentRow = SIZE/2;
  currentCol = SIZE/2;
  currentDir = 0;
  currentColor = red;
  drawOn = true;
}

// The other constructor is used to start the turtle at a particular row/col
// and in any given direction. Since we cannot change the constructor
// signature, we always set the turtle to red and will draw it.
Turtle::Turtle(double initialRow, double initialCol, double initialDir) {
  currentRow = initialRow;
  currentCol = initialCol;
  currentDir = initialDir;
  currentColor = red;
  drawOn = true;
}

// This function will move the turtle object by the distance parameter. We use
// trigonometry to decide how far in each orthogonal direction we want to move,
// and we have to convert to radians using the constant M_PI. The if statement
// will only draw the turtle if it is set to draw, otherwise the movement will
// take place but nothing will be drawn.
void Turtle::move(double distance) {
  double startingRow = currentRow;
  double startingCol = currentCol;
  currentRow += distance * cos(currentDir * M_PI / 180);
  currentCol += distance * sin(currentDir * M_PI / 180);
  if(drawOn) {
    std_draw_line(currentColor, startingRow, startingCol, currentRow, currentCol);
  }
}

// This function is simple: it just changes the direction of the turtle.
void Turtle::turn(double degree) {
  currentDir += degree;
}

// This function changes the color of the turtle. Notice that the variable 
// type is color, which is defined in the bmplib.h file. 
void Turtle::setColor(color newColor) {
  currentColor = newColor;
}

// This makes the turtle draw function turned on.
void Turtle::on() {
  drawOn = true;
}
// This turns off the turtle and makes it so it will not be drawn to the screen.
void Turtle::off() {
  drawOn = false;
}
