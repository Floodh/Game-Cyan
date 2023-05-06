#include "Land.hpp"
#include "Console.hpp"

#include <iostream>
#include <math.h>

#define ELEVATION 0.5f

using namespace std;

int calculateIndexCount(uint8_t* levelData, int levelHeight, int levelWidth);
void normalizeVec3(GLfloat* data);

Land::Land(Camera& camera, TheSun& theSun, uint8_t* levelData, int levelWidth, int levelHeight, GLfloat* const backgroundColor)
    : backgroundColor{backgroundColor}, camera{camera}, theSun{theSun}
{

    this->shader = loadShaders("shader/land.vert", "shader/land.frag");
    //  world data contaisn information about the quads NOT the vertexes
    // int vertexHeight = levelHeight + 1;
    // int vertexWidth = levelWidth + 1;

    //  bgra
    //  world generation here

        this->indexCount = calculateIndexCount(levelData, levelHeight, levelWidth);
        this->vertexCount = ( indexCount / ( 2 * 3 * 5) ) * 8;  //  8 points per cube
        this->valueCount = vertexCount * 3;

        this->indices = new GLint[indexCount];
        this->vertices = new GLfloat[valueCount];
        this->colors = new GLfloat[valueCount];

        {
        GLuint countVert = 0; 
        GLuint countColor = 0; 
        GLuint countIndex = 0;

        int countCubes = 0;
        for (int z = 0; z < levelHeight; z++)
        
            for (int x = 0; x < levelWidth; x++)
            {
                int indexOffset = ((z * levelWidth) + x) * 4;       //  may need to modify this multipler if the world data structyre changes
                if (levelData[indexOffset] == 75 && levelData[indexOffset + 1] == 105 && levelData[indexOffset + 2] == 47)
                {
                    //  create cube/rectangle
                        vertices[countVert++] = (GLfloat)(levelWidth - x);
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)(levelWidth - (x + 1));
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)(levelWidth - (x + 1));
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)(z + 1);

                        vertices[countVert++] = (GLfloat)(levelWidth - x);
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)(z + 1);                    

                        vertices[countVert++] = (GLfloat)(levelWidth - x);
                        vertices[countVert++] = (GLfloat)0;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)(levelWidth - (x + 1));
                        vertices[countVert++] = (GLfloat)0;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)(levelWidth - (x + 1));
                        vertices[countVert++] = (GLfloat)0;
                        vertices[countVert++] = (GLfloat)(z + 1);

                        vertices[countVert++] = (GLfloat)(levelWidth - x);
                        vertices[countVert++] = (GLfloat)0;
                        vertices[countVert++] = (GLfloat)(z + 1);      

                    //  set the colors (maybe replace it with textures?)
                        //  green feilds on top
                        for (int i = 0; i < 4; i++)
                        {
                            this->colors[countColor++] = 0.005;   //  r
                            this->colors[countColor++] = 0.083;   //  g
                            this->colors[countColor++] = 0.0;   //  b
                        }
                        //  grey below
                        for (int i = 0; i < 4; i++)
                        {
                            this->colors[countColor++] = 0.03;   //  r
                            this->colors[countColor++] = 0.03;   //  g
                            this->colors[countColor++] = 0.03;   //  b
                        }

                    //  set the indexes
                        int indexOffset = countCubes * 8;
                        //  top 1
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 2; 
                        //  top
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 2; 
                        indices[countIndex++] = indexOffset + 3; 

                        //  bottom
                        //  top 1
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 4; 
                        //  top
                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 5; 
                        indices[countIndex++] = indexOffset + 4; 
                        //  top
                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 2; 
                        indices[countIndex++] = indexOffset + 5; 
                        //  top
                        indices[countIndex++] = indexOffset + 2; 
                        indices[countIndex++] = indexOffset + 6; 
                        indices[countIndex++] = indexOffset + 5; 

                        //  top
                        indices[countIndex++] = indexOffset + 2; 
                        indices[countIndex++] = indexOffset + 3; 
                        indices[countIndex++] = indexOffset + 6; 
                        //  top
                        indices[countIndex++] = indexOffset + 3; 
                        indices[countIndex++] = indexOffset + 7; 
                        indices[countIndex++] = indexOffset + 6; 
                        //  top
                        indices[countIndex++] = indexOffset + 3; 
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 7; 
                        //  top
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 4; 
                        indices[countIndex++] = indexOffset + 7; 


                    countCubes++;

                }
            }
        
        if ( (countIndex != this->indexCount) | (countVert != this->valueCount) | (countColor != this->valueCount) )
        {
            cout << "Landmass counters does not match the expected values, countIndex = " << countIndex << "/" << this->indexCount << ", countVert = " << countVert << "/" << this->valueCount << ", countColor = " << countColor << "/" << this->valueCount << endl;
            exit(1);
        }
        } 

              
    //  create data for rendering
    glGenVertexArrays(1, &vertexArrayObjID);


    glGenBuffers(1, &indexBufferObjID);
    glGenBuffers(1, &vertexBufferObjID);
    glGenBuffers(1, &colorBufferObjID);
    glGenBuffers(1, &normalBufferObjID);
    
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

}

void Land::Draw()
{
    glUseProgram(shader);
    //  when camera is fixed, use this
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniform3fv(glGetUniformLocation(shader, "eyePosition"), 1, this->camera.realPosition);

    glUniform3fv(glGetUniformLocation(shader, "playerPosition"), 1, this->camera.realPosition);


	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}



//  help functions

int calculateIndexCount(uint8_t* levelData, int levelHeight, int levelWidth)
{
    int greenPixels = 0;
    //  for optimazation one might wanna calculate

    for (int i = 0; i < levelWidth * levelHeight; i++)
    {
        int indexOffset = i * 4;
        if ( (levelData[indexOffset] == 75) & (levelData[indexOffset + 1] == 105) & (levelData[indexOffset + 2] == 47) )
            greenPixels++; 
    }
    return greenPixels * 2 * 3 * 5;    //  multiplied by five because were making a partial cube    
}


//  normalizes a vector(x, y, z)
void normalizeVec3(GLfloat* data)
{
    GLfloat norm = (GLfloat)sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
    data[0] = data[0] / norm;
    data[1] = data[1] / norm;
    data[2] = data[2] / norm;
}