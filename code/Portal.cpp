#include "Portal.hpp"

#include <iostream>

using namespace std;

Portal::Portal(GLfloat x, GLfloat y, GLfloat z, Player& player, Camera& camera, GLfloat* backgroundColor)
    : player{player}, transformMatrix{new GLfloat[16]}, camera{camera}
{

    this->shape = VertexShape_Diamond(0.0, 0.0, 0.0, 0.5f, 1.0f);
    this->shape.shader = loadShaders("shader/portal.vert", "shader/portal.frag");

    for (int i = 0; i < 16; i++)
        this->transformMatrix[i] = 0.0f;
    for (int i = 0; i < 16; i += 5)
        this->transformMatrix[i] = 1.0f;
        
    SetPosition(x,y,z);

    

    //  finish the colors
    for (int i = 0; i < this->shape.valueCount;)
    {
        this->shape.colors[i++] = 0.5f;
        this->shape.colors[i++] = 0.2f;
        this->shape.colors[i++] = 0.5f;
    }

    glBindBuffer(GL_ARRAY_BUFFER, shape.vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, shape.vertexCount*3*sizeof(GLfloat), shape.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shape.shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shape.shader, "inPosition"));	 

    glBindBuffer(GL_ARRAY_BUFFER, shape.colorBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, shape.vertexCount*3*sizeof(GLfloat), shape.colors, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shape.shader, "inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shape.shader, "inColor"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexCount*sizeof(GLuint), shape.indices, GL_STATIC_DRAW);    

    glUniformMatrix4fv(glGetUniformLocation(shape.shader, "projectionMatrix"), 1, GL_TRUE, this->camera.GetProjectionMatrix());
    glUniform3fv(glGetUniformLocation(shape.shader, "backgroundColor"), 1, backgroundColor);

}

void Portal::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->transformMatrix[3] = this->x;
    this->transformMatrix[7] = this->y;
    this->transformMatrix[11] = this->z;

    //glBindVertexArray(shape.vertexArrayObjID);
    glUseProgram(this->shape.shader);
    glUniformMatrix4fv(glGetUniformLocation(shape.shader, "transformMatrix"), 1, GL_TRUE, this->transformMatrix);

}

void Portal::Draw()
{
    glUseProgram(this->shape.shader);
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniform3fv(glGetUniformLocation(shape.shader, "eyePosition"), 1, this->camera.position);

	glBindVertexArray(this->shape.vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, this->shape.indexCount, GL_UNSIGNED_INT, 0L);
}


bool Portal::IsPlayerInside()
{
    
    GLfloat dx, dz;

    dx = this->x - player.getPosition().x;
    dz = this->z - player.getPosition().z; 

    GLfloat distance = sqrt(dx * dx + dz * dz);

    return distance < 1.0f;

}
