#pragma once
#include "SDL.h"
#include "GL_utilities.h"

#include <iostream>

//  I/O inspired by C#'s console class
namespace Console
{
    //  print string
    void WriteLine(std::string const& content);
    //  print 1d array
    void WriteLine(GLfloat* value, const int size);
    //  print 1d array as 2d matrix
    void WriteLine(GLfloat* value, const int width, const int height);
};