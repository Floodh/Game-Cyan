//  these needs to be included in this order,
//  openGl is not allowed to be included before GL_utilities
#include "SDL.h"
#include "GL_utilities.h"


#include <string>
#include <iostream>
#include <iomanip> // for setw


#include "Terrain.hpp"

int main(int argc, char *argv[])
{
    int screen_width = 640, screen_height = 480;
    SDL_Window * main_window = nullptr;
    SDL_GLContext gl_context = nullptr;
    SDL_Event event = { 0 };
    bool should_quit = false;

    // TRY-CATCH TO FACILITATE COMMON CLEAN-UP CODE
    try {

        // INITIALIZE SDL:
        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            throw(std::string("Failed to initialize SDL: ") + SDL_GetError());
        }

        // CONFIGURE OPENGL ATTRIBUTES USING SDL:
        int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // CREATE AND SDL WINDOW CONFIGURED FOR OPENGL:
        if (0 == (main_window = SDL_CreateWindow("OpenGL Init Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL))) {
            throw(std::string("Failed to create window: ") + SDL_GetError());
        }

        // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
        if(NULL == (gl_context = SDL_GL_CreateContext(main_window))) {
            throw(std::string("Failed to create OpenGL context"));
        }
        else SDL_GL_MakeCurrent(main_window, gl_context);

        // INITIALIZE GLAD:
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            throw(std::string("Failed to initialize GLAD"));
        }

        // LOG OPENGL VERSION, VENDOR (IMPLEMENTATION), RENDERER, GLSL, ETC.:
        std::cout << std::setw(34) << std::left << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
        std::cout << std::setw(34) << std::left << "OpenGL Shading Language Version: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        std::cout << std::setw(34) << std::left << "OpenGL Vendor:" << (char *)glGetString(GL_VENDOR) << std::endl;
        std::cout << std::setw(34) << std::left << "OpenGL Renderer:" << (char *)glGetString(GL_RENDERER) << std::endl;

        //auto gProgramID = glCreateProgram();
        Terrain t = Terrain();

        // GAME LOOP:
        while (!should_quit) {
            // EVENT LOOP:
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        should_quit = true;
                        break;
                    }
                    break;
                }
            }

            // RENDERING GOES HERE:
            // ...
            // Clear the screen to WHITE:
            glClearColor(1.f, 1.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            t.Draw();

            // DRAW A ROUND RECTANGLE WITH AN OUTLINE:
            float rect_w = 250.f, rect_h = 250.f;

            // PRESENT BACKBUFFER:
            SDL_GL_SwapWindow(main_window);
        }
    }
    catch (std::string e) {
        std::cout << e << std::endl;;
    }
    catch (...) {
        std::cout << "Unknown exception caught!" << std::endl;
    }

    if (gl_context) SDL_GL_DeleteContext(gl_context);
    if (main_window) SDL_DestroyWindow(main_window);
    SDL_Quit();

    return 0;
}