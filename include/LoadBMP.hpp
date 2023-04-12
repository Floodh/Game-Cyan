#pragma once


// #include "SDL.h"
#include "GL_utilities.h"

#include <string>



//  load .bmp file, return pointer to floats stored in it
//  format should be: red, green, blue, alpha
//  the size of the .bmp file should be equal to the number of pixels times 4
//  width and height should get their apropiet values(should be found in the header of the .bmp file)
//  it turns out that sending the int values is better than converting them to floats
//  keep in mind that the values of the pixels are stored in byte, which is to say they are not floats
uint8_t* LoadBMP(char const *path, int& width, int& height, int& channels);
