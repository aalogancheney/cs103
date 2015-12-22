#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// SIZE has been declared in the bmplib.h header file. 
unsigned char image[SIZE][SIZE];

// Prototypes for our functions. 
void draw_rectangle(int top, int left, int height, int width);
void draw_ellipse(int cy, int cx, int height, int width);


int main() {

    // Initializes the image to all white, so that we don't have garbage in
    // some parts of the array.
    for(int i = 0; i < SIZE; i++) {
        for(int j=0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }

    // Prompts to the user to enter the desired information.
    cout << "To draw a rectangle, enter: 0 top left height width." << endl;
    cout << "To draw an ellipse, enter: 1 cy cx height width." << endl;
    cout << "To save your drawing as \"output.bmp\" and quit, enter 2." << endl;

    // Declares variables that are used in the command and drawing process. 
    int command;
    int value1;
    int value2;
    int value3;
    int value4;

    // I ask for the command first so that if the command is 2 the other entries
    // will never be read and the program will exit immediately. 
    cin >> command;

    // This while loop continues so long as there is no case where the command entered
    // is 2. There is a case to handle the command as an invalid command. 
    while(command != 2) {
        // These are placed inside the while loop so that we can exit as soon
        // as the quit command is reached. 
        cin >> value1 >> value2 >> value3 >> value4;
        // Prints the image to the file, and shows the user confirmation of their
        // entry.        
        if(command == 0) {
            draw_rectangle(value1, value2, value3, value4);
            cout << "Thank you for that rectangle." << endl;
        }
        // Prints the image to the file and again gives confirmation to the user. 
        else if(command == 1) {
            draw_ellipse(value1, value2, value3, value4);
            cout << "Thank you for that ellipse." << endl;
        }
        else {
            cout << "That is not a valid command; please try again: " << endl;
        }
        // Reissues the commands and reminds the user what they are entering. 
        cout << "To draw a rectangle, enter: 0 top left height width." << endl;
        cout << "To draw an ellipse, enter: 1 cy cx height width." << endl;
        cout << "To save your drawing as \"output.bmp\" and quit, enter 2." << endl;
        cin >> command; // >> value1 >> value2 >> value3 >> value4;
    }
    

    // Write the resulting image to the .bmp file
    writeGSBMP("output.bmp", image);

    return 0;
}

void draw_rectangle(int top, int left, int height, int width) {
    // This for loop will draw the horizontal parts of the rectangle. The inner
    // if statements will check to see if the points along the horizontal
    // segments are within the image size. The first if statement checks if
    // the particular i is within the range, and the two inner if statements
    // draw the top and bottom lines. As an example, if the top coordinate is
    // outside the image size, it will not be drawn at all because no matter how
    // far it extends on either side it will never be part of the image.      
    for(int i = left; i < width + left + 1; i++) {
        if(i > 0 && i < SIZE) {
            if(top > 0 && top < SIZE) {
                image[top][i] = 0;
            }
            if(top + height > 0 && top + height < SIZE) {
                image[top + height][i] = 0;
            }
        }
        // These outside if statements will print the rectangle as it is being
        // drawn. 
        // if (i % 10 == 0) {showGSBMP(image);}
    }
    
    // This for loop handles the vertical parts of the rectangle. Similar to 
    // how the above if statements work, the vertical segments are only printed
    // if they fall in the range of the image. Thus, if any part of the rectangle
    // is outside of the image, it won't be printed. This means if the user
    // enters the starting coordinates outside the image, part of the rectangle 
    // will still be printed if it becomes within the range of the image.   
    for (int i = top; i < height + top + 1 && i < SIZE; i++) {        
        if(i > 0 && i < SIZE) { 
            if(left > 0 && left < SIZE) {       
                image[i][left] = 0;
            }
            if(left + width > 0 && left + width < SIZE) {
                image[i][left + width] = 0;
            }
        }
        // if (i % 10 == 0) {showGSBMP(image);}
    }
}

void draw_ellipse(int cy, int cx, int height, int width) {
    int iteration = 0;
    // This for loop iterates over 2PI radians at an increment of 0.01 radians.    
    for(double theta = 0.0; theta < 2 * M_PI; theta += .01) {    
        // I declare and initialize variables for the appropriate x and y coordinates.
        int x = width * cos(theta);
        int y = height * sin(theta);
        // These update commands shift the circle/ellipse to the desired origin point.         
        x += cx;
        y += cy;
        // The if statement checks to see if the value is within the range of the image,
        // and if it is that coordinate of the ellipse gets printed on screen. 
        if(x < SIZE && y < SIZE && y > 0 && x > 0) {
            image[y][x] = 0;
        }
        // Since we are working with a double as our counter in the for loop we
        // cannot utilize the modulus operation to show the image. Therefore, 
        // outside the for loop I declared an integer counter that gets incremented
        // and the image will show every 10 steps. 
        iteration++;
        // if (iteration % 10 == 0) {showGSBMP(image);}
    }    
}
