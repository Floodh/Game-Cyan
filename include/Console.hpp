#pragma once
#include "SDL.h"
#include "GL_utilities.h"

#include <iostream>

//  I/O inspired by C#'s console class
class Console
{
    void WriteLine(std::string content);
    void WriteLine(GLfloat* value, const int size);
    void WriteLine(GLfloat* value, const int width, const int height);
};