#include "Player.hpp"


#include <iostream>



Player::Player(Camera& camera, uint8_t* levelData, int width, int height)
: camera{camera}, HP{100}, Points{0}, scale{0.5f}, levelData{levelData}, width{width}, height{height}
{
    this->position = {2.0f, 0.5f*(scale+0.5f), 1.5f};

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

    if ( (movement.x != 0.0f) | (movement.y != 0.0f) | (movement.z != 0.0f) ) //    don't normalize a vector that has no direction
    {
        movement = normalize(movement);
    }
    
    
    

    vec3 tmp_pos = this->position + (abs(this->m->normalArray->z) * this->scale * movement);

    int z = floor(tmp_pos.z);
    int x = width - floor(tmp_pos.x) - 1.0; //  inverted weirdness
    int index = (x*4+z*width*4);

    if ((int)this->levelData[index] == 75 && (int)this->levelData[index+1] == 105 && (int)this->levelData[index+2] == 47)
        this->position += 0.05f * movement;
        
    camera.SetLookAt(position.x, position.y, position.z);
    camera.SetPosition(position.x, position.y + 1.5f, position.z - 1.75f);
}


void Player::Draw()
{
    glUseProgram(shader);
  
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix.m);
    glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, GL_TRUE, T(position.x, position.y, position.z).m);

	DrawModel(m, shader, "inPosition", NULL, NULL);
}

void Player::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position.x = x;
    this->position.y = y; // We may not want to change the y-value here
    this->position.z = z;
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
