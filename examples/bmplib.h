#ifndef BMPLIB_H
#define BMPLIB_H

#define SIZE 256
#define RGB 3


int readRGBBMP(const char* filename, unsigned char inputImage[][SIZE][RGB]);
int writeRGBBMP(const char* filename, unsigned char outputImage[][SIZE][RGB]);
int readGSBMP(const char* filename, unsigned char image[][SIZE]);
int writeGSBMP(const char* filename, unsigned char outputImage[][SIZE]);




#endif
