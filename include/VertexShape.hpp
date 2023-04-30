#pragma once

#include "SDL.h"
#include "GL_utilities.h"

struct VertexShape
{
    // vertex array object
    unsigned int vertexArrayObjID;

    unsigned int indexBufferObjID;
    unsigned int vertexBufferObjID;
    unsigned int colorBufferObjID;

    GLuint indexCount;
    GLuint vertexCount;    
    GLuint valueCount;

    GLint* indices;
    GLfloat* vertices;
    GLfloat* colors;
    
    GLuint shader = NULL;

};

//  return a vertex shape that will be drawn as a dome
//  you still need to color it yourself
VertexShape VertexShape_Dome(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);

//  return a vertex shape that will be drawn as a stretched out diamond
//  you still need to color it yourself
VertexShape VertexShape_Diamond(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat ratio);


