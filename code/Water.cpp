#include "Water.hpp"

Water::Water(Camera& camera)
    : camera{camera}
{
    this->shader = loadShaders("shader\\water.vert", "shader\\water.frag");


    //  world generation here
        this->indexCount = 6;
        this->vertexCount = 4;    
        this->valueCount = vertexCount * 3;

        //  create a test quad
        this->vertices = new GLfloat[valueCount]{
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0,
        };
        this->colors = new GLfloat[valueCount]{
            0.0, 0.0, 0.5,
            1.0, 0.0, 0.5,
            1.0, 1.0, 0.5,
            0.0, 1.0, 0.5,
        };
        this->indices = new GLint[indexCount]
        {
            0, 1, 3,
            1, 2, 3 
        };

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

}

void Water::Draw()
{
	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}
