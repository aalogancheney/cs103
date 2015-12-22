#include "bmplib3.h"  // Used because we use variables of type color

// This class is called Turtle, and is designed to draw objects to the screen
// using the bmplib3.cpp library. 
class Turtle {
  // This public area is used for declaring function prorotypes that are going
  // to be used with this class. 
  public:
    Turtle();
    Turtle(double initialRow, double initialCol, double initialDir);
    void move(double distance);
    void turn(double degree);
    void setColor(color newColor);
    void off();
    void on();
  // This private section is used to hold data members for the Turtle class,
  // since the data members should be private. 
  private:
    double currentRow;
    double currentCol;
    double currentDir;
    bool drawOn;
    color currentColor;
};
