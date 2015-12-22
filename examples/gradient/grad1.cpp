#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

unsigned char bwimage[SIZE][SIZE];
unsigned char rgbimage[SIZE][SIZE][RGB];

// 0 means black, 255 means white.
// SIZE = 256.

int main()
{
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            bwimage[i][j] = i;
        }
    }

    writeGSBMP("grad1.bmp", bwimage);

    return 0;
}



