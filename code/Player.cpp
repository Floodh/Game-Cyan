#include "Player.hpp"


#include <iostream>



Player::Player(Camera& camera, uint8_t* levelData, int width, int height)
: camera{camera}, HP{100}, Points{0}, scale{0.3f}, levelData{levelData}, width{width}, height{height}
{
    this->position = {2.0f, 0.5f*(scale+1.0f), 1.5f};

    this->shader = loadShaders("shader/player.vert", "shader/player.frag");
    this->scaleMatrix = S(scale);
    this->rotationMatrix = IdentityMatrix();
    this->m = LoadModel("data/model/cubeplus.obj");
 

	glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));

	glVertexAttribPointer(glGetAttribLocation(this->shader, "inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inColor"));

    glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, GL_TRUE, this->camera.GetProjectionMatrix());
    glUniform3fv(glGetUniformLocation(shader, "eyePosition"), 1, this->camera.position);

    glUniformMatrix4fv(glGetUniformLocation(shader, "scaleMatrix"), 1, GL_TRUE, this->scaleMatrix.m);
}

Player::Player(Camera& camera, uint8_t* levelData, int width, int height, GLfloat x, GLfloat y, GLfloat z, GLfloat* backgroundColor)
: camera{camera}, HP{100}, Points{0}, scale{1.0f}, levelData{levelData}, width{width}, height{height}
{
    this->shape = VertexShape_Diamond(x, y, z, 0.3f, 1.0f);
    this->shape.shader = loadShaders("shader/player.vert", "shader/player.frag");
    this->shader = 99;
    this->scaleMatrix = S(scale);
    this->rotationMatrix = IdentityMatrix();
    this->position = {x, y, z};


     //  finish the colors
    for (GLuint i = 0; i < this->shape.valueCount;)
    {
        this->shape.colors[i++] = 1.0f;
        this->shape.colors[i++] = 0.5f;
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

    glUniform3fv(glGetUniformLocation(shape.shader, "eyePosition"), 1, this->camera.position);

    glUniformMatrix4fv(glGetUniformLocation(shape.shader, "scaleMatrix"), 1, GL_TRUE, this->scaleMatrix.m);
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "transformationMatrix"), 1, GL_TRUE, T(this->position.x, this->position.y, this->position.z).m);

}


Player::~Player()
{}


void Player::Update(Keyboard* kb)
{
    vec3 movement{0.0f, 0.0f, 0.0f};

    if (kb->GetKey(119).keypress) //  W
    {
        // movement.x += sin(0.0f);
        movement.z += 1;//cos(0.0f);
    }
    if (kb->GetKey(115).keypress) //  S
    {
        // movement.x += -sin(0.0f);
        movement.z += -1;//-cos(0.0f);
    }
     if (kb->GetKey(97).keypress) //  A
    {
        movement.x += 1;//sin(1.5f);
        // movement.z += cos(1.5f);
    }
    if (kb->GetKey(100).keypress) //  D
    {
        movement.x += -1;//-sin(1.5f);
        // movement.z += -cos(1.5f); 
    }

    // No need to normalize since all changes are size 1, also normalization generates a player bug when near edge

    // if ( (movement.x != 0.0f) | (movement.y != 0.0f) | (movement.z != 0.0f) ) //    don't normalize a vector that has no direction
    // {
    //     movement = normalize(movement);
    // }
    vec3 tmp_pos;
    if (this->shader != 99)
    {
        tmp_pos = this->position + (abs(this->m->normalArray->z) * this->scale * movement);
    }
    else
    {
        tmp_pos = this->position + 0.5f * movement;
    }  

    int z = floor(tmp_pos.z);
    int x = width - floor(tmp_pos.x) - 1.0; //  inverted weirdness
    int index = (x*4+z*width*4);

    if ((int)this->levelData[index] == 75 && (int)this->levelData[index+1] == 105 && (int)this->levelData[index+2] == 47)
        // setPosition(tmp_pos.x, tmp_pos.y, tmp_pos.z);
        this->position += 0.05f * movement;
        
    
    // if (kb->GetKey(1073741906).keypress) //  up
    // {
    //     camera.SetPosition(position.x, position.y + 1.5f, camera.position[2] + 0.05f);
    //     // this->world->camera.position[2] += 0.05f;

    // }
    // else if (kb->GetKey(1073741905).keypress) //  down
    // {
    //     camera.SetPosition(position.x, position.y + 1.5f, camera.position[2] - 0.05f);
    //     // this->world->camera.position[2] -= 0.05f;
    // }
    // // else
    
    camera.SetLookAt(position.x, position.y, position.z);
    camera.SetPosition(position.x, position.y + 1.5f, position.z - 1.75f);
}


void Player::Draw()
{
    if (shader != 99)
    {

        glUseProgram(shader);
    
        glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
        glUniformMatrix4fv(glGetUniformLocation(shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix.m);
        glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, GL_TRUE, T(position.x, position.y, position.z).m);

        DrawModel(m, shader, "inPosition", NULL, NULL);
    }
    else
    {
        glUseProgram(this->shape.shader);
        glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
        glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix.m);

        glUniform3fv(glGetUniformLocation(this->shape.shader, "eyePosition"), 1, this->camera.position);
        glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "transformationMatrix"), 1, GL_TRUE, T(this->position.x, this->position.y, this->position.z).m);
        glBindVertexArray(this->shape.vertexArrayObjID);    // Select VAO
        glDrawElements(GL_TRIANGLES, this->shape.indexCount, GL_UNSIGNED_INT, 0L);
    }
}

void Player::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position.x = x;
    this->position.y = y; // We may not want to change the y-value here
    this->position.z = z;

    // this->transformMatrix[3] = x;
    // this->transformMatrix[7] = y;
    // this->transformMatrix[11] = z;

    // //glBindVertexArray(shape.vertexArrayObjID);
    glUseProgram(this->shape.shader);
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "transformationMatrix"), 1, GL_TRUE, T(this->position.x, this->position.y, this->position.z).m);

}

void Player::updateLevel(uint8_t* levelData, int width, int height)
{
    this->levelData = levelData;    
    this->width = width;
    this->height = height;
}


const vec3& Player::getPosition()
{
    return this->position;
}
