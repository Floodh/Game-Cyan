#pragma once

#include "IDrawObject.hpp"
#include "GL_utilities.h"
#include "Camera.hpp"
#include "LittleOBJLoader.h"
#include "VectorUtils4.h"
#include "Keyboard.hpp"
#include "VertexShape.hpp"



#define PLAYERTURNSPEED 0.055f

class Player : public IDrawObject
{
    public:
        Player(Camera& camera, uint8_t* levelData, int width, int height, GLfloat x, GLfloat y, GLfloat z, GLfloat* backgroundColor);
        // Player(GLint* m, GLint* texture);
        ~Player();

        void Update(Keyboard* kb);
        void Draw();

        void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);
        const vec3& getPosition();

        void updateLevel(uint8_t* levelData, int width, int height);
        void setColor(GLfloat R, GLfloat G, GLfloat B);


    private:
        Camera &camera;
        vec3 position;
        GLfloat radiantAngle = 0.0;

        // Stats        
        int HP;
        int Points;


        GLuint numVertices;
        GLfloat* pyramidVertices;
        GLfloat* colors;
        unsigned int vertexArrayObjID;
        GLfloat scale;
        mat4 scaleMatrix;
        GLfloat*  rotationMatrix;

        VertexShape shape;
        uint8_t* levelData = nullptr;
        int width;
        int height;
        
};
