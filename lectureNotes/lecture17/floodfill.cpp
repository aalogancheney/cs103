#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

unsigned char image[SIZE][SIZE];

// This part was added in lecture19. 
// These objects are public by default.
struct Point {
  int row;
  int col;
};

struct Rectangle {
  Rectangle(int upperLeftRow, int upperLeftColumn, int height0, int width0);
  Point upperLeft;
  int height;
  int width; 
};

Rectangle::Rectangle(int upperLeftRow, int upperLeftColumn, int height0, int width0) {
  upperLeft.row = upperLeftRow;
  upperLeft.col = upperLeftColumn;
  height = height0;
  width = width0;
}

// Prototypes
void print_menu();
void draw_rectangle(Rectangle rectangle);
void draw_ellipse(int cr, int cc, int a, int b);
void flood_fill(int cr, int cc);

void print_menu()
{
  cout << "\nTo draw a rectangle, enter: 0 upper-left-row upper-left-col height width" << endl;
  cout << "To draw an ellipse, enter: 1 center_pt_row center_pt_col major-len minor-len" << endl;
  cout << "To fill an area with black, enter: 2 pt_row pt_col" << endl;
  cout << "To save your drawing as \"output.bmp\" and quit, enter: 3" << endl;
  cout << "\nEnter choice: " << endl;
}
int main()
{
  int choice, ulr, ulc, h, w, cr, cc, a, b;
  choice = -1;
  // initialize the image to all white pixels
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      image[i][j] = 255;
    }
  }

  while(choice != 3){
    print_menu();
    cin >> choice;
    if(choice == 0){
      cin >> ulr >> ulc >> h >> w;
      Rectangle rectangle(ulr, ulc, h, w);
      draw_rectangle(rectangle);
    }
    else if(choice == 1){
      cin >> cr >> cc >> a >> b;
      draw_ellipse(cr, cc, a, b);
    }
    else if(choice == 2){
      cin >> cr >> cc;
      flood_fill(cr, cc);
    }
  }
  writeGSBMP("output.bmp", image);
  return 0;
}

void draw_rectangle(Rectangle rectangle)
{
  for(int r=rectangle.upperLeft.row; r < rectangle.upperLeft.row+rectangle.height; r++){
    // cout << r << " " << rectangle.upperLeft.row << "\t" << r << " " << ulc+w << endl;
    image[r][rectangle.upperLeft.col] = 0;
    image[r][rectangle.upperLect.col+rectangle.width] = 0;
  }
  for(int c=rectangle.upperLeft.col; c < rectangle.upperLeft.col+rectangle.width; c++){
    // cout << ulr << " " << c << "\t" << ulr+h << " " << c << endl;
    image[rectangle.upperLeft.row][c] = 0;
    image[rectangle.upperLeft.row+rectangle.height][c] = 0;
  }
}

void draw_ellipse(int cr, int cc, int a, int b)
{
  double r = a/2;
  for(double theta=0.0; theta < 2*M_PI; theta += .01){
    int x = r*cos(theta);
    int y = (b/2)*sin(theta);
    x += cc;
    y += cr;
    image[y][x] = 0;
  }
}

void flood_fill(int r, int c)
{
  if(r < 0 || r > 255 || c < 0 || c > 255) {
    return;
  }  
  else if(image[r][c] == 0) {
    return;
  }
  else {
    image[r][c] = 0;
    flood_fill(r + 1, c);
    flood_fill(r - 1, c);
    flood_fill(r, c + 1);
    flood_fill(r, c - 1);
  }
}
