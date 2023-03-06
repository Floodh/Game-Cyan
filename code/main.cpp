#include <iostream>

#include "SDL.h"
#include "GraphicUnit.hpp"
#include "Terrain.hpp"

using namespace std;


int main(int argc, char **argv){

    cout << "start" << endl;





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
        //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



        //SDL_GL_SwapBuffers();
        SDL_GL_SwapWindow(gu->window);
        
    }
    gu->exit();

    cout << "\nend";
    return 0;

}