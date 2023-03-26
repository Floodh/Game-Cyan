#include "Game.hpp"

#include <string>
#include <iostream>
#include <iomanip> // for setw

using namespace std;


Game::Game(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;


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
    if (0 == (this->window = SDL_CreateWindow("OpenGL Init Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowWidth, SDL_WINDOW_OPENGL))) {
        throw(std::string("Failed to create window: ") + SDL_GetError());
    }

    // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
    if(NULL == (this->glContext = SDL_GL_CreateContext(this->window))) {
        throw(std::string("Failed to create OpenGL context"));
    }
    else SDL_GL_MakeCurrent(this->window, this->glContext);

    // INITIALIZE GLAD:
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw(std::string("Failed to initialize GLAD"));
    }

    // LOG OPENGL VERSION, VENDOR (IMPLEMENTATION), RENDERER, GLSL, ETC.:
    std::cout << std::setw(34) << std::left << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Shading Language Version: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Vendor:" << (char *)glGetString(GL_VENDOR) << std::endl;
    std::cout << std::setw(34) << std::left << "OpenGL Renderer:" << (char *)glGetString(GL_RENDERER) << std::endl;

}

Game::~Game()
{
    if (this->glContext) SDL_GL_DeleteContext(this->glContext);
    if (this->window) SDL_DestroyWindow(this->window);
}


void Game::Draw()
{
    SDL_GL_SwapWindow(this->window);
}


// Terrain::Terrain(Camera& camera)
// {
//     GLfloat vertices[] = {
//             -0.5f,-0.5f,0.0f,
//             -0.5f,0.5f,0.0f,
//             0.5f,-0.5f,0.0f
//         };

//     // this->landmassVertices = vertices;
//     // this->shader = loadShaders("shader/water.vert", "shader/water.frag");

// 	// glGenVertexArrays(1, &this->vertexArrayObjID);
// 	// glBindVertexArray(this->vertexArrayObjID);
// 	// // Allocate Vertex Buffer Objects
// 	// glGenBuffers(1, &this->vertexBufferObjID);
	
// 	// // VBO for vertex data
// 	// glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObjID);
// 	// glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), this->landmassVertices, GL_STATIC_DRAW);
// 	// glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
// 	// glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));  

// 	//	VBO for color data


// 	//	add possibly texture here for animation data

// // }

// void Terrain::Draw()
// {
// 	// glBindVertexArray(this->vertexArrayObjID);	// Select VAO
// 	// glDrawArrays(GL_TRIANGLES, 0, 3);	    // draw object  
// }