#pragma once


// #include "SDL.h"
#include "GL_utilities.h"

#define STBI_ONLY_BMP
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>



//  load .bmp file, return pointer to floats stored in it
//  format should be: red, green, blue, alpha
//  the size of the .bmp file should be equal to the number of pixels times 4
//  width and height should get their apropiet values(should be found in the header of the .bmp file)
//  it turns out that sending the int values is better than converting them to floats
//  keep in mind that the values of the pixels are stored in byte, which is to say they are not floats
GLfloat* LoadBMP(char const *path, int& width, int& height, int& channels)
{
    return stbi_loadf(path, &width, &height, &channels, 0);
}