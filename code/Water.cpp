#include "Water.hpp"

#include <iostream>

//  green(land) 75 105 47
//  blue(water) 99 155 255

Water::Water(Camera& camera)
    : camera{camera}
{

    this->shader = loadShaders("shader/water.vert", "shader/water.frag");

    //  world data contaisn information about the quads NOT the vertexes
    int worldHeight = 3;
    int worldWidth = 3;
    int vertexHeight = worldHeight + 1;
    int vertexWidth = worldWidth + 1;
    GLint* worldData = new GLint[worldHeight * worldWidth * 4]  //  placeholder for testing
    {
        99, 155, 255,
        99, 155, 255,
        99, 155, 255,

        99, 155, 255,
        75, 105, 47,
        99, 155, 255,

        99, 155, 255,
        99, 155, 255,
        99, 155, 255
    };



    //  world generation here
        this->indexCount = worldHeight * worldWidth * 2 * 3;    //  number of quads multiplied by 2 to get number of triangles, multiplied by 3 to get number of indexes for the triangles.
        this->vertexCount = vertexHeight * vertexWidth;         //  
        this->valueCount = vertexCount * 3;                     //  we have 3 values for each vertex

        this->indices = new GLint[indexCount];
        this->vertices = new GLfloat[valueCount];
        this->colors = new GLfloat[valueCount];


        //  initlize all indexes for indicies
        {
        GLuint count = 0;
        for (int z = 0; z < worldHeight; z++)
            for (int x = 0; x < worldWidth; x++)
            {
                int p1Index = (z * worldWidth) + x;
                int p2Index = (z * worldWidth) + x + 1;
                int p3Index = ((z + 1) * worldWidth) + x;
                int p4Index = ((z + 1) * worldWidth) + x + 1;

                //  this may not be clockwise, this could cause problems with culling and calculating normals
                this->indices[count++] = p1Index;
                this->indices[count++] = p2Index;
                this->indices[count++] = p3Index;

                this->indices[count++] = p2Index;
                this->indices[count++] = p3Index;
                this->indices[count++] = p4Index;
            }
        if (count != indexCount)
        {
            std::cout << "The loaded index values for water generation does not match the indexCount(array size), count = " << count << ", indexCount = " << indexCount << std::endl;
            exit(1);
        }
        }

        //  initlize all vertexes coords and color
        for (int z = 0; z < vertexHeight; z++)
            for (int x = 0; x < vertexWidth; x++)
            {
                GLfloat vertexX = (GLfloat)x;
                GLfloat vertexY = (GLfloat)0.0f;
                GLfloat vertexZ = (GLfloat)z;

                GLfloat r = vertexX / vertexHeight, g = vertexZ / vertexHeight,b = 0.9;    //  placeholder values, will be determined by worldData


                int indexOffset = ((z * worldWidth) + x) * 3;
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
    

}

void Water::Draw()
{
    //  when camera is fixed, use this
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());

	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}
