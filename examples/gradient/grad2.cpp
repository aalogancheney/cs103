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
        for(int j = 0; j < i + 1; j++) {
            bwimage[i - j][j] = i;
            bwimage[SIZE - (i - j) - 1][SIZE - j - 1] = i;
        }
    }

    writeGSBMP("grad2.bmp", bwimage);

    return 0;
}



