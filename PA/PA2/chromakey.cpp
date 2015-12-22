/*********************************************************************
 File:              chromakey.cpp
 Author:            Aaron Cheney
 Email address:     acheney@usc.edu

 Usage: 
 program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp
 One execution of the program will yield two outputs, using method1()
 and method2().

 Method 1: Utilize a user-defined distance threshold from the
           chromakey value as a discriminator.

 Method 2: Samples the background image and decides on an acceptable
           deviation from the background for each R, G, and B value.

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"
#include <algorithm>

using namespace std;

// These cannot be changed because the graders need to use these 
// exact names. Also, note that SIZE is declared inside bmplib.h
// as 256 so we have a uniform size for the images we are processing.

// Method 1, as outlined in the Programming Assignment.
void method1(unsigned char inImage[][SIZE][RGB], 
               bool mask[][SIZE],
               double threshold);

// Method 2, designed by me to improve Method 1 by removing the 
// dependency on a threshold. 
void method2(unsigned char inImage[][SIZE][RGB], 
               bool mask[][SIZE]);

// Merges the input image with the mask to produce the output image. 
void replace(bool mask[][SIZE],
               unsigned char inImage[][SIZE][RGB],
               unsigned char bgImage[][SIZE][RGB],
               unsigned char outImage[][SIZE][RGB]);

// Finds the average R, G, or B value, depending on the color
// argument, in the first i rows and j columns, determined by the
// row and column arguments. 
double averageRGB(unsigned char inImage[][SIZE][RGB], 
                  int row, int column, int color);

// Calculates distance from the chromakey.
double distanceRGB(unsigned char inImage[][SIZE][RGB],
                   double chromaR, 
                   double chromaG, 
                   double chromaB,
                   int row, int column);

// Finds the minimum R, G, or B value while disregarding a number
// of values outside the tollerance range from the average. 
int minimumRGB(unsigned char inImage[][SIZE][RGB], 
               int row, int column, int color,
               int average, int tollerance);

// Same as above but for the maximum. 
int maximumRGB(unsigned char inImage[][SIZE][RGB], 
               int row, int column, int color,
               int average, int tollerance);

// Resets the mask array to all 0's. 
void resetChromaMask(bool mask[SIZE][SIZE]);

// There are many times where using 0, 1, or 2 to reference the
// R, G, and B values are needed, so these constants are defined. 
const int R = 0;
const int G = 1;
const int B = 2;

int main(int argc, char *argv[]) {
  
  // The keyword static permanently creates data in a separate chunk
  // of memory, and is usually considered bad practice, although we
  // will use it here in place of dynamically allocated memory. 
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  // If there are fewer than 6 arguments presented on the command 
  // line, the program will show the user the proper inputs that 
  // are needed, and will exit properly.
  // Also, note that cerr is the standard output stream for errors,
  // which can be used in place of cout. 
  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp "
         << "dist_threshold out1.bmp out2.bmp" << endl;
    return 0;
  }

  // Recall that readRGBBMP() will return a non-zero value if it does
  // not execute properly. The error message will be displayed
  // if the file cannot be read. 
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  // The same case for above, but with the background image. 
  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Converts the 4th element of argv[] to a double value using the
  // atof() function.
  threshold = atof(*(argv + 3));
  
  // Call method1() and create the output image to be written to
  // a file.
  method1(inputImage, chromaMask, threshold);
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }    

  // Resets the chromaMask array for the next use. 
  resetChromaMask(chromaMask);

  // Call method2() and create the output image. 
  method2(inputImage, chromaMask);
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }    

  return 0;
}

// method1() takes the input image, the mask array, and the user-
// determined threshold value to make the mask.
void method1(unsigned char inImage[][SIZE][RGB], 
               bool mask[][SIZE],
               double threshold) {

  // Let's assume that the first 3 rows and the first 3 columns
  // will always be part of the background of any greenscreen
  // image. This computes the average R, G, and B values.
  int row = 3;
  int column = 3;
  double averageR = averageRGB(inImage, row, column, R);
  double averageG = averageRGB(inImage, row, column, G);
  double averageB = averageRGB(inImage, row, column, B);
  
  // This construction will use the average values, calculated
  // above, with the user-input threshold to set the mask
  // array appropriately. 
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      if(distanceRGB(inImage, averageR, averageG, averageB, i, j)
            < threshold) {
        mask[i][j] = false;
      } else {
        mask[i][j] = true;
      }
    }
  }
}

// method2() considers each component of RGB separately to
// try and differentiate what makes the background unique
// from the foreground, rather than use a raw distance
// formula as in method1().
void method2(unsigned char inImage[][SIZE][RGB], 
               bool mask[][SIZE]) {
  
  // We will assume that the fist 3 rows and the first 3
  // columns will always be part of the chromakey. The
  // extremeTollerance variable is passed to the 
  // maximumRGB() and minimumRGB() functions to 
  // decide when a particular pixel falls outside of the
  // tollerance for maximum and minimum R, G, and B 
  // values. The allowance variable is a fudge factor. 
  int row = 3;
  int column = 3;
  int extremeTollerance = 30;
  int allowance = 2;
  
  // Finds average values for R, G, and B.
  double averageR = averageRGB(inImage, row, column, R);
  double averageG = averageRGB(inImage, row, column, G);
  double averageB = averageRGB(inImage, row, column, B);
  
  // Finds the minimum values of R, G, and B.
  int minimumR = minimumRGB(inImage, row, column, R,
                            averageR, extremeTollerance);
  int minimumG = minimumRGB(inImage, row, column, G,
                            averageG, extremeTollerance);
  int minimumB = minimumRGB(inImage, row, column, B,
                            averageB, extremeTollerance);
  
  // Finds the maximum values of R, G, and B.
  int maximumR = maximumRGB(inImage, row, column, R,
                            averageR, extremeTollerance);
  int maximumG = maximumRGB(inImage, row, column, G,
                            averageG, extremeTollerance);
  int maximumB = maximumRGB(inImage, row, column, B,
                            averageB, extremeTollerance);
  
  // Creates acceptable boudnds for R, G, and B
  // with the maximum and minimum values for each 
  // R, G, and B, and factors in the allowance value.
  int redBound = abs(minimumR - maximumR) + allowance;
  int greenBound = abs(minimumG - maximumG) + allowance;
  int blueBound = abs(minimumB - maximumB) + allowance;
  
  // Iterates over all pixels, requiring that all three
  // components (R, G, and B) be within an acceptable 
  // range of the average values for each R, G, and B.
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      if(abs(inImage[i][j][R] - averageR) < redBound
            && abs(inImage[i][j][G] - averageG) < greenBound
            && abs(inImage[i][j][B] - averageB) < blueBound) {
        mask[i][j] = false;
      } else {
        mask[i][j] = true;
      }
    }
  }
}

// This function decides how to set the values in the outImage
// array based on the mask array. The outImage is made entirely of
// either a pixel from the inImage or the bgImage. 
void replace(bool mask[][SIZE],
               unsigned char inImage[][SIZE][RGB],
               unsigned char bgImage[][SIZE][RGB],
               unsigned char outImage[][SIZE][RGB]) {

  // This construction creates the output image based on the 
  // mask using a simple logical comparison and iterating over 
  // all pixels in the outImage array. 
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      for(int k = 0; k < RGB; k++) {
        if(mask[i][j]) {
          outImage[i][j][k] = inImage[i][j][k];
        } else {
          outImage[i][j][k] = bgImage[i][j][k];
        }
      }
    }
  }
}

// This function computes the average R, G, or B value of a picture
// based on the first 'row' rows and 'column' columns. The return
// value will give the average for a particular color of the image. 
double averageRGB(unsigned char inImage[][SIZE][RGB], 
                  int row, int column, int color) {
  
  // Iterates over the first 'column' columns to get 
  // the average value of the 'color' variable.
  double average = 0;
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < column; j++) {
      average += inImage[i][j][color];
    }
  }
  
  // Iterates over the first 'row' rows to get the average 
  // value of the 'color' variable.
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < SIZE; j++) {
      average += inImage[i][j][color];
    }
  }
  
  // Adjusts the average for the total number of sampled 
  // pixels of the image. Here we subtract row * column 
  // so that we don't double count their values. 
  average /= SIZE * (row + column) - (row * column);

  return average;
}

// This function calculates the maximum value of R, G, or B
// in the first 'row' rows and 'column' columns. 
int maximumRGB(unsigned char inImage[][SIZE][RGB], 
               int row, int column, int color,
               int average, int tollerance) {
  
  // This counter is used to exclude the 10 most maximum 
  // values in the case that part of the foreground is 
  // in the firse few rows/columns. 
  int count = 10;

  // Iterates over the rows and decides if each pixel is
  // in the acceptable range for being considered a 
  // maximum value.
  int maximum = inImage[0][0][color];
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < column; j++) {
      if(inImage[i][j][color] > maximum) {
        if(count > 0 && abs(inImage[i][j][color] - 
           average) > tollerance) {
          count--;
        } else {
          maximum = inImage[i][j][color];
        }
      }
    }
  }

  // Resets count to be used again for the columns, and
  // the same process as above is repeated. 
  count = 10;
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < SIZE; j++) {
      if(inImage[i][j][color] > maximum) {
        if(count > 0 && abs(inImage[i][j][color] - 
           average) > tollerance) {
          count--;
        } else {
          maximum = inImage[i][j][color];
        }
      }
    }
  }

  return maximum;
}

// This function calculates the minimum value of R, G, or B
// in the first 'row' rows and 'column' columns. The internal
// processes are the same as in the maximum() function.
int minimumRGB(unsigned char inImage[][SIZE][RGB], 
               int row, int column, int color,
               int average, int tollerance) {
  
  int count = 10;
  int minimum = inImage[0][0][color];
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < column; j++) {
      if(inImage[i][j][color] < minimum) {
        if(count > 0 && abs(inImage[i][j][color] - 
           average) > tollerance) {
          count--;
        } else {
          minimum = inImage[i][j][color];
        }
      }
    }
  }

  count = 10;
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < SIZE; j++) {
      if(inImage[i][j][color] < minimum) {
        if(count > 0 && abs(inImage[i][j][color] - 
           average) > tollerance) {
          count--;
        } else {
          minimum = inImage[i][j][color];
        }
      }
    }
  }

  return minimum;
}

// This function computes the distance between each 
// pixel and a chromakey as determined by the 
// averageRGB() function. 
double distanceRGB(unsigned char inImage[][SIZE][RGB],
                   double chromaR, 
                   double chromaG, 
                   double chromaB,
                   int row, int column) {

  double distance = 
    sqrt(pow(chromaR - inImage[row][column][R], 2) + 
         pow(chromaG - inImage[row][column][G], 2) +
         pow(chromaB - inImage[row][column][B], 2));

  return distance;
}

// This function resets the chromaMask array to all zeros.
void resetChromaMask(bool mask[SIZE][SIZE]) {
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      mask[i][j] = false;
    }
  }
}
