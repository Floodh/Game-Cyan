#include "Water.hpp"

#include <iostream>
#include <stdlib.h>
//  green(land) 75 105 47
//  blue(water) 99 155 255

//  https://www.enkisoftware.com/devlogpost-20150131-1-Normal-generation-in-the-pixel-shader
//  https://c0de517e.blogspot.com/2008/10/normals-without-normals.html

using namespace std;

#define WATERLEVEL 0.425f

Water::Water(Camera& camera, uint8_t* levelData, int levelWidth, int levelHeight, GLfloat* const backgroundColor, int& frameCount)
    : backgroundColor{backgroundColor}, camera{camera}, frameCount{frameCount}
{
    
    std::cout << "Generating water level: " << levelWidth << "x" << levelHeight << std::endl;

    this->shader = loadShaders("shader/water.vert", "shader/water.frag");

    //  world data contaisn information about the quads NOT the vertexes
    int detailMultipler = 2;

    int vertexHeight = (levelHeight * detailMultipler) + 1;
    int vertexWidth = (levelWidth * detailMultipler) + 1;



    //  world generation here
        this->indexCount = levelWidth * levelHeight * 2 * 3 * detailMultipler * detailMultipler;    //  number of quads multiplied by 2 to get number of triangles, multiplied by 3 to get number of indexes for the triangles.
        this->vertexCount = vertexHeight * vertexWidth;         //  
        this->valueCount = vertexCount * 3;                     //  we have 3 values for each vertex

        this->indices = new GLint[indexCount];
        this->vertices = new GLfloat[valueCount];
        this->colors = new GLfloat[valueCount];


        //  initlize all indexes for indicies
        {
        GLuint count = 0;
        for (int z = 0; z < vertexHeight - 1; z++)
            for (int x = 0; x < vertexWidth - 1; x++)
            {

                int p1Index = (z * vertexWidth) + x;
                int p2Index = (z * vertexWidth) + x + 1;
                int p3Index = ((z + 1) * vertexWidth) + x;
                int p4Index = ((z + 1) * vertexWidth) + x + 1;

                //  this may not be clockwise, this could cause problems with culling and calculating normals
                this->indices[count++] = p1Index;
                this->indices[count++] = p2Index;
                this->indices[count++] = p3Index;

                this->indices[count++] = p3Index;
                this->indices[count++] = p4Index;
                this->indices[count++] = p2Index;

            }
        if (count != indexCount)
        {
            std::cout << "The loaded index values for water generation does not match the indexCount(array size), count = " << count << ", indexCount = " << indexCount << std::endl;
            exit(1);
        }
        }
        std::cout << std::endl;

        //  initlize all vertexes coords and color
        for (int z = 0; z < vertexHeight; z++)
            for (int x = 0; x < vertexWidth; x++)
            {
                //cout << "Vertex " << x << " " << z << endl;

                GLfloat vertexX = (GLfloat)x / detailMultipler;
                GLfloat vertexY = (GLfloat)0.125f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) / 8;
                GLfloat vertexZ = (GLfloat)z / detailMultipler;

                GLfloat r = vertexX / vertexHeight, g = vertexZ / vertexHeight,b = 0.9;    //  placeholder values, will be determined by worldData


                int indexOffset = ((z * vertexWidth) + x) * 3;
                this->vertices[indexOffset + 0] = vertexX;
                this->vertices[indexOffset + 1] = vertexY;
                this->vertices[indexOffset + 2] = vertexZ;

                this->colors[indexOffset + 0] = r;
                this->colors[indexOffset + 1] = g;
                this->colors[indexOffset + 2] = b;
            }


    //  


    //  create data for rendering
    glGenVertexArrays(1, &vertexArrayObjID);


    glGenBuffers(1, &indexBufferObjID);
    glGenBuffers(1, &vertexBufferObjID);
    glGenBuffers(1, &colorBufferObjID);
    
    glBindVertexArray(vertexArrayObjID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shader, "inPosition"));	 

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(GLfloat), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shader, "inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shader, "inColor"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLuint), indices, GL_STATIC_DRAW);

    glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, GL_TRUE, this->camera.GetProjectionMatrix());
    glUniform3fv(glGetUniformLocation(shader, "backgroundColor"), 1, this->backgroundColor);


    this->randomYPosition0 = new GLfloat[this->vertexCount];
    this->randomYPosition1 = new GLfloat[this->vertexCount];
    for (GLuint i = 0; i < this->vertexCount; i++)
    {
        this->randomYPosition0[i] = (((GLfloat)rand()) / RAND_MAX) * WATERLEVEL;
        this->randomYPosition1[i] = (((GLfloat)rand()) / RAND_MAX) * WATERLEVEL;
    }
}

void Water::Draw()
{
    glUseProgram(shader);

    //  animate the vertexes
    GLfloat howMuch = (0.5 * sin((GLfloat)this->frameCount / 35.0) + 0.5);
    //howMuch = (GLfloat)(this->frameCount % 75) / 74.0;
    for (GLuint i = 0; i < this->vertexCount; i++)
    {  
        this->vertices[(i * 3) + 1] = howMuch * this->randomYPosition0[i] + (1.0 - howMuch) * this->randomYPosition1[i];
        if (howMuch <= 0.01f)
            this->randomYPosition0[i] = (((GLfloat)rand()) / RAND_MAX) * WATERLEVEL;
        else if (howMuch >= 0.99f)
            this->randomYPosition1[i] = (((GLfloat)rand()) / RAND_MAX) * WATERLEVEL;
    }
    



    //  when camera is fixed, use this
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniform3fv(glGetUniformLocation(shader, "eyePosition"), 1, this->camera.realPosition);

    glUniform3fv(glGetUniformLocation(shader, "playerPosition"), 1, this->camera.realPosition);



	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shader, "inPosition"));

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}
