#pragma once

#include "SDL.h"
#include "GL_utilities.h"


//  may need to move the support data types 
//  if the need for a in game menu arises

struct Rect
{
    int x, y, width, height;
};

struct Button
{
    Button() = default; //  needed because cpp oop feutures are kinda restrivtive

    Button(
        Rect area, 
        bool enabled, bool visible, 
        GLfloat* color, unsigned int bufferIndex
    )
        :   area{area},
            enabled{enabled}, visible{visible}, 
            holdingClick{false}, clicked{false},
            clickedFrame{-1}, color{color},
            bufferIndex{bufferIndex}
    {}

    Rect area;
    bool enabled;
    bool visible;
    bool holdingClick;
    bool clicked;
    int clickedFrame; 

    GLfloat* color; //  vec3

    unsigned int bufferIndex;
};


class MainMenu
{

    public:

        MainMenu(const int & windowWidth, const int & windowHeight);
        void Update();
        void Draw();

    private:

        Button playButton;
            Button map1Button;
            // Button map2;
            // Button map3;
        
        Button quitButton;

        const int& windowWidth;
        const int& windowHeight; 


        void DrawButton(const Button& button);



        //  these are mainted by the main menu instance but are referanced by the buttons

        // vertex array object
        unsigned int vertexArrayObjID;

        unsigned int indexBufferObjID;
        unsigned int vertexBufferObjID;

        //  variables for drawing rectangles
        GLuint indexCount;
        GLuint vertexCount;    
        GLuint valueCount;

        GLfloat* vertices;
        GLint* indices;

        GLuint shader;
        void DrawRect(Rect rect, GLfloat* color);


};