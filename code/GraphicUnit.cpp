
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include "math.h"
//#include <GL/glu.h>


#include "SDL.h"
#include "GraphicUnit.hpp"

using namespace std;

//  help function
    void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
    {
        const GLdouble pi = 3.1415926535897932384626433832795;
        GLdouble fW, fH;

        //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
        fH = tan( fovY / 360 * pi ) * zNear;
        fW = fH * aspect;

        glFrustum( -fW, fW, -fH, fH, zNear, zFar );
    }

    // void loadResource(void)
    // {
    //     // vertex buffer object, used for uploading the geometry
    //     unsigned int vertexBufferObjID;
    //     // Reference to shader program
    //     GLuint program;

    //     // Load and compile shader
    //     program = loadShaders("lab1-1.vert", "lab1-1.frag");
    //     //printError("init shader");
    //     // Upload geometry to the GPU:

    //     // Allocate and activate Vertex Array Object
    //     glGenVertexArrays(1, &vertexArrayObjID);
    //     glBindVertexArray(vertexArrayObjID);
    //     // Allocate Vertex Buffer Objects
    //     glGenBuffers(1, &vertexBufferObjID);

    //     // VBO for vertex data
    //     glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    //     glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    //     glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    //     glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

    //     // End of upload of geometry

    //     printError("init arrays");
    // }


//  GraphiUnit
void GraphicUnit::setup(const char window_name[]){

    int bpp = 0;


    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "Warning: Failed to initialize" << endl;
    }

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    this->window = SDL_CreateWindow("test", 500 , 500 , this->window_width , this->window_height , SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_OPENGL);
    this->renderer = SDL_CreateRenderer(window, 0, 0);

    this->glContext = SDL_GL_CreateContext(this->window);
    if (this->glContext == 0)
    {
        cout << "Warning: Failed to create GL context" << endl;
    }

    float ratio = (float) this->window_width / (float) this->window_height;

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    /* Setup our viewport. */
    glViewport( 0, 0, this->window_width, this->window_height );

    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    perspectiveGL( 60.0, ratio, 1.0, 1024.0 );

}
void GraphicUnit::exit(){
    SDL_Quit();
}



