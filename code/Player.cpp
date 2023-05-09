#include "Player.hpp"


#include <iostream>




Player::Player(Camera& camera, uint8_t* levelData, int width, int height, GLfloat x, GLfloat y, GLfloat z, GLfloat* backgroundColor)
    : camera{camera}, HP{100}, Points{0}, scale{1.0f}, levelData{levelData}, width{width}, height{height} 
{
    this->shape = VertexShape_Diamond(x, y, z, 0.2f, 1.5f);
    this->shape.shader = loadShaders("shader/player.vert", "shader/player.frag");
    this->scaleMatrix = S(scale);
    this->rotationMatrix = new GLfloat[16]{
		cos(this->radiantAngle), 0.0f, sin(this->radiantAngle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(this->radiantAngle), 0.0f, cos(this->radiantAngle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

    this->position = {x, 0.785f, z};


     //  finish the colors
    setColor(255.0f, 2.0f, 2.0f);



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

    if (kb->GetKey(97).keypress) //  A
        this->radiantAngle += PLAYERTURNSPEED;
    if (kb->GetKey(100).keypress) //  D
        this->radiantAngle -= PLAYERTURNSPEED;


    
    if (kb->GetKey(119).keypress) //  W
    {
        movement.x += sin(this->radiantAngle);
        movement.z += cos(this->radiantAngle);
    }

    if (kb->GetKey(115).keypress) //  S
    {
        movement.x -= sin(this->radiantAngle);
        movement.z -= cos(this->radiantAngle);
    }
    
    if (kb->GetKey(1073742049).keypress) //  Shift
    {
        movement = movement*1.75;
    }

    if (kb->GetKey(32).keypress && position.y <= 1.0f) //  Space
    {
        position.y += 0.02f;
    } 
    else if (position.y >= 0.785f)
    {
        position.y -= 0.02f;
    }
    
    vec3 tmp_pos;
    tmp_pos = this->position + 0.05f * movement;
     

    int z = floor(tmp_pos.z);
    int x = width - floor(tmp_pos.x) - 1.0; //  inverted weirdness
    int index = (x*4+z*width*4);

    if ((int)this->levelData[index] == 75 && (int)this->levelData[index+1] == 105 && (int)this->levelData[index+2] == 47)
        this->position += 0.05f * movement;
    //
	rotationMatrix[0] =	cos(this->radiantAngle / 1.0);
	rotationMatrix[2] = sin(this->radiantAngle / 1.0);
    rotationMatrix[8] = -sin(this->radiantAngle / 1.0);
    rotationMatrix[10] = cos(this->radiantAngle / 1.0);
    
    camera.SetLookAt(position.x, position.y, position.z);
    camera.SetPosition(position.x - sin(this->radiantAngle) * 3.5, position.y + 1.4f, position.z - cos(this->radiantAngle) * 3.5);

}


void Player::Draw()
{

    glUseProgram(this->shape.shader);
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix);

    glUniform3fv(glGetUniformLocation(this->shape.shader, "eyePosition"), 1, this->camera.position);
    glUniformMatrix4fv(glGetUniformLocation(this->shape.shader, "transformationMatrix"), 1, GL_TRUE, T(this->position.x, this->position.y, this->position.z).m);
    glBindVertexArray(this->shape.vertexArrayObjID);    // Select VAO
    glDrawElements(GL_TRIANGLES, this->shape.indexCount, GL_UNSIGNED_INT, 0L);
    
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

void Player::setColor(GLfloat R, GLfloat G, GLfloat B)
{
    for (GLuint i = 0; i < this->shape.valueCount;)
    {
        this->shape.colors[i++] = R;
        this->shape.colors[i++] = G;
        this->shape.colors[i++] = B; 
    } 
    glBindBuffer(GL_ARRAY_BUFFER, shape.colorBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, shape.vertexCount*3*sizeof(GLfloat), shape.colors, GL_STATIC_DRAW);
}