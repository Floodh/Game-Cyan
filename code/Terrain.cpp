#include "Terrain.hpp"

#include <iostream>

using namespace std;

Terrain::Terrain()
{
    GLfloat vertices[] = {
            -0.5f,-0.5f,0.0f,
            -0.5f,0.5f,0.0f,
            0.5f,-0.5f,0.0f
        };

	std::cout << "1" << std::endl;
    this->landmassVertices = vertices;
    this->shader = loadShaders("shader/water.vert", "shader/water.frag");
	std::cout << "2" << std::endl;
	glGenVertexArrays(1, &this->vertexArrayObjID);
	glBindVertexArray(this->vertexArrayObjID);
	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &this->vertexBufferObjID);
	
	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), this->landmassVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));  

}

void Terrain::Draw()
{
	glBindVertexArray(this->vertexArrayObjID);	// Select VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	    // draw object  
}