#include "Player.hpp"
#include <iostream>
#include "Console.hpp"

Player::Player(Camera& camera, uint8_t* levelData, int width, int height)
: camera{camera}, HP{100}, Points{0}, scale{0.3f}, width{width}, height{height}
{
    // this->position = new GLfloat[3]{0.0f, 100.0f, 5.0f};
    this->position = {2.0f, 0.65f, 1.5f};

    this->shader = loadShaders("shader/player.vert", "shader/player.frag");
    this->scaleMatrix = S(scale);
    this->rotationMatrix = IdentityMatrix();

    this->levelData = levelData;
    
    // this->numVertices = 3 * 3 * 6;

    this->m = LoadModel("data/model/cubeplus.obj");
 
    
    // unsigned int vertexBufferObjID;
	// unsigned int fragmentBufferObjID;l

    // this->pyramidVertices = new GLfloat[3*18]{
    
    //     0.5f, 0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,

    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,


    // //
    //     0.5f, 0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,

    //     -0.5f, 0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,

    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f,

    //     0.5f, -0.5f, 0.0f,
    //     0.5f, 0.5f, 0.0f,
    //     0.0f, 0.0f, 0.5f};

    

    // this->colors = new GLfloat[3*3]
    //     {
    //         0.5f, 0.0f, 0.0f,
    //         0.0f, 0.5f, 0.0f,
    //         0.0f, 0.0f, 0.5f};
    // // Allocate and activate Vertex Array Object
    // glGenVertexArrays(1, &vertexArrayObjID);
	// glBindVertexArray(vertexArrayObjID);

    // // Allocate Vertex Buffer Objects
	// glGenBuffers(1, &vertexBufferObjID);

    // // VBO for vertex data
	// glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	// glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));

    // VBO for vertex data
	// glGenBuffers(1, &fragmentBufferObjID);

	// glBindBuffer(GL_ARRAY_BUFFER, fragmentBufferObjID);
	// glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(this->shader, "inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inColor"));
	//

	// glUniformMatrix4fv(glGetUniformLocation(this->shader, "tranformationMatrix"), 1, GL_TRUE, tranformationMatrix);
	// glUniformMatrix4fv(glGetUniformLocation(this->shader, "rotationMatrix"), 1, GL_TRUE, rotationMatrix);


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

    if ( (movement.x != 0.0f) | (movement.y != 0.0f) | (movement.z != 0.0f) ) //    don't normalize a vector that has no direction
    {
        // movement = normalize(movement);
    }
    
    
    

    vec3 tmp_pos = this->position + (abs(this->m->normalArray->z) * this->scale * movement);

    int z = floor(tmp_pos.z);
    int x = width - floor(tmp_pos.x) - 1.0; //  inverted weirdness

    // std::cout << "Debug:" << std::endl;
    // std::cout << "      x = " << x << ", z = " << z << std::endl;
    
    

    int index = (x*4+z*width*4);

    // std::cout << "      index = " << index << std::endl;
  
    if ((int)this->levelData[index] == 75 && (int)this->levelData[index+1] == 105 && (int)this->levelData[index+2] == 47)
        this->position += 0.05f * movement;

    //std::cout << "levelData: " << (int)this->levelData[index] << " levelData: "<< (int)this->levelData[index+1] << " levelData: " << (int)this->levelData[index+2] << " levelData: " << (int)this->levelData[index+3] << std::endl;
    // if (this->levelData[index] == 99 & this->levelData[index+1] == 155 & this->levelData[index+2] == 255 & this->levelData[index+3] == 255)
 
 
    //     std::cout << "      Blue" << std::endl;
    // else 
    //     std::cout << "      Green" << std::endl;

    

    // std::cout << std::endl;

    //Console::WriteLine(this->levelData, width, height, 4);
    
    // for (int index = 0; index < this->width * this->height * 4; index +=4)
    // {
    //     std::cout << (int)this->levelData[index] << " " << (int)this->levelData[index+1] << " " << (int)this->levelData[index+2] << " " << (int)this->levelData[index+3] << " " << std::endl;
    // }
        






    camera.SetLookAt(position.x, position.y, position.z);
    camera.SetPosition(position.x, position.y + 1.5f, position.z - 1.75f);

}


void Player::Draw()
{
    glUseProgram(shader);
  
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix.m);
    glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, GL_TRUE, T(position.x, position.y, position.z).m);



    //glBindVertexArray(vertexArrayObjID); // Select VAO
	DrawModel(m, shader, "inPosition", NULL, NULL);
    //glDrawArrays(GL_TRIANGLES, 0, numVertices / 3);	 // draw object
}

void Player::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position.x = x;
    this->position.y = y; // We may not want to change the y-value here
    this->position.z = z;
}


const vec3& Player::getPosition()
{
    return this->position;
}
