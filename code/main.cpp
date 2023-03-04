#include <iostream>
#include <windows.h>
#include <gl/gl.h>

#include "SDL.h"
#include "GraphicUnit.hpp"

using namespace std;


int main(int argc, char **argv){

    cout << "start" << endl;

    GLfloat angle = 0.1f;
    GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
    GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
    GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
    GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
    GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
    GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
    GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
    GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
    GLubyte red[]    = { 255,   0,   0, 255 };
    GLubyte green[]  = {   0, 255,   0, 255 };
    GLubyte blue[]   = {   0,   0, 255, 255 };
    GLubyte white[]  = { 255, 255, 255, 255 };
    GLubyte yellow[] = {   0, 255, 255, 255 };
    GLubyte black[]  = {   0,   0,   0, 255 };
    GLubyte orange[] = { 255, 255,   0, 255 };
    GLubyte purple[] = { 255,   0, 255,   0 };



    GraphicUnit *gu = new GraphicUnit();

    gu->setup("test");
    bool run = true;
    while (run)
    {
        SDL_Event event;
        while ( SDL_PollEvent(&event))
        {
            /* code */
            if (event.type == SDL_QUIT)
            {
                run = false;
            }
        }
        /* Clear the color and depth buffers. */
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        /* We don't want to modify the projection matrix. */
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );
        glTranslatef( 0.0, 0.0, -5.0 );
        glRotatef( angle, angle, angle, 0.0 );

        if( true ) {
            angle += 0.01;
            if( angle > 360.0f ) {
                angle = 0.0f;
            }
        }
        //  draw Triangles
            glBegin( GL_TRIANGLES );

            glColor4ubv( red );
            glVertex3fv( v0 );
            glColor4ubv( green );
            glVertex3fv( v1 );
            glColor4ubv( blue );
            glVertex3fv( v2 );

            glColor4ubv( red );
            glVertex3fv( v0 );
            glColor4ubv( blue );
            glVertex3fv( v2 );
            glColor4ubv( white );
            glVertex3fv( v3 );

            glColor4ubv( green );
            glVertex3fv( v1 );
            glColor4ubv( black );
            glVertex3fv( v5 );
            glColor4ubv( orange );
            glVertex3fv( v6 );

            glColor4ubv( green );
            glVertex3fv( v1 );
            glColor4ubv( orange );
            glVertex3fv( v6 );
            glColor4ubv( blue );
            glVertex3fv( v2 );

            glColor4ubv( black );
            glVertex3fv( v5 );
            glColor4ubv( yellow );
            glVertex3fv( v4 );
            glColor4ubv( purple );
            glVertex3fv( v7 );

            glColor4ubv( black );
            glVertex3fv( v5 );
            glColor4ubv( purple );
            glVertex3fv( v7 );
            glColor4ubv( orange );
            glVertex3fv( v6 );

            glColor4ubv( yellow );
            glVertex3fv( v4 );
            glColor4ubv( red );
            glVertex3fv( v0 );
            glColor4ubv( white );
            glVertex3fv( v3 );

            glColor4ubv( yellow );
            glVertex3fv( v4 );
            glColor4ubv( white );
            glVertex3fv( v3 );
            glColor4ubv( purple );
            glVertex3fv( v7 );

            glColor4ubv( white );
            glVertex3fv( v3 );
            glColor4ubv( blue );
            glVertex3fv( v2 );
            glColor4ubv( orange );
            glVertex3fv( v6 );

            glColor4ubv( white );
            glVertex3fv( v3 );
            glColor4ubv( orange );
            glVertex3fv( v6 );
            glColor4ubv( purple );
            glVertex3fv( v7 );

            glColor4ubv( green );
            glVertex3fv( v1 );
            glColor4ubv( red );
            glVertex3fv( v0 );
            glColor4ubv( yellow );
            glVertex3fv( v4 );

            glColor4ubv( green );
            glVertex3fv( v1 );
            glColor4ubv( yellow );
            glVertex3fv( v4 );
            glColor4ubv( black );
            glVertex3fv( v5 );

            glEnd();

        //SDL_GL_SwapBuffers();
        SDL_GL_SwapWindow(gu->window);
        
    }
    gu->exit();

    cout << "\nend";
    return 0;

}