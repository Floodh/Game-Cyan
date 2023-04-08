#include "Land.hpp"


#include <iostream>

#define ELEVATION 1.0f

using namespace std;

int calculateIndexCount(GLint* worldData, int worldWidth, int worldHeight);

Land::Land(Camera& camera)
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

        this->indexCount = calculateIndexCount(worldData, worldWidth, worldHeight);
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
        for (int z = 0; z < vertexHeight; z++)
        
            for (int x = 0; x < vertexWidth; x++)
            {
                int indexOffset = ((z * worldWidth) + x) * 3;       //  may need to modify this multipler if the world data structyre changes
                if (worldData[indexOffset] == 75 && worldData[indexOffset + 1] == 105 && worldData[indexOffset + 2] == 47)
                {
                    //  create cube/rectangle
                        vertices[countVert++] = (GLfloat)x;
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)x +1;
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)x;
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z + 1;

                        vertices[countVert++] = (GLfloat)x + 1;
                        vertices[countVert++] = (GLfloat)ELEVATION;
                        vertices[countVert++] = (GLfloat)z + 1;                    

                        vertices[countVert++] = (GLfloat)x;
                        vertices[countVert++] = (GLfloat)-ELEVATION;    //  maybe set this to just zero?
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)x +1;
                        vertices[countVert++] = (GLfloat)-ELEVATION;
                        vertices[countVert++] = (GLfloat)z;

                        vertices[countVert++] = (GLfloat)x;
                        vertices[countVert++] = (GLfloat)-ELEVATION;
                        vertices[countVert++] = (GLfloat)z + 1;

                        vertices[countVert++] = (GLfloat)x + 1;
                        vertices[countVert++] = (GLfloat)-ELEVATION;
                        vertices[countVert++] = (GLfloat)z + 1;   

                    //  set the colors
                        //  green feilds on top
                        for (int i = 0; i < 4; i++)
                        {
                            this->colors[countColor++] = 0.3;   //  r
                            this->colors[countColor++] = 0.8;   //  g
                            this->colors[countColor++] = 0.1;   //  b
                        }
                        //  grey below
                        for (int i = 0; i < 4; i++)
                        {
                            this->colors[countColor++] = 0.6;   //  r
                            this->colors[countColor++] = 0.7;   //  g
                            this->colors[countColor++] = 0.4;   //  b
                        }
                    //  set the indexes
                        int indexOffset = countCubes * 8;
                        indices[countIndex++] = indexOffset + 0; 
                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 2; 

                        indices[countIndex++] = indexOffset + 1; 
                        indices[countIndex++] = indexOffset + 2; 
                        indices[countIndex++] = indexOffset + 3; 

                        for (int i = 0; i < 4; i++)
                        {
                            indices[countIndex++] = indexOffset + i + 0; 
                            indices[countIndex++] = indexOffset + i + 1; 
                            indices[countIndex++] = indexOffset + i + 0 + 4;   

                            indices[countIndex++] = indexOffset + i + 1; 
                            indices[countIndex++] = indexOffset + i + 1 + 4; 
                            indices[countIndex++] = indexOffset + i + 0 + 4;
                        }

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

void Land::Draw()
{
    //  when camera is fixed, use this
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());

	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}


int calculateIndexCount(GLint* worldData, int worldWidth, int worldHeight)
{
    int greenPixels = 0;
    //  for optimazation one might wanna calculate

    for (int i = 0; i < worldHeight * worldWidth; i++)
    {
        int indexOffset = i * 3;
        if (worldData[indexOffset] == 75 & worldData[indexOffset + 1] == 105 & worldData[indexOffset + 2] == 47)
            greenPixels++; 
    }
    return greenPixels * 2 * 3 * 5;    //  multiplied by five because were making a partial cube    
}
