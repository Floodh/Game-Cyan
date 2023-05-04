#pragma once

#include "IDrawObject.hpp"
#include "GL_utilities.h"
#include "Camera.hpp"
#include "LittleOBJLoader.h"
#include "VectorUtils4.h"
#include "Keyboard.hpp"


class Player : public IDrawObject
{
    public:
        Player(Camera& camera, uint8_t* levelData, int width, int height);
        // Player(GLint* m, GLint* texture);
        ~Player();

        void Update(Keyboard* kb);
        void Draw();

        void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);
        const vec3& getPosition();

        void updateLevel(uint8_t* levelData, int width, int height);


    private:
        Camera &camera;
        vec3 position;

        // Stats        
        int HP;
        int Points;

        GLuint shader;
        GLuint numVertices;
        GLfloat* pyramidVertices;
        GLfloat* colors;
        unsigned int vertexArrayObjID;
        GLfloat scale;
        mat4 scaleMatrix;
        mat4 rotationMatrix;

        Model* m;
        uint8_t* levelData = nullptr;
        int width;
        int height;
        
};
