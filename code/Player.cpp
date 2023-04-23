#include "Player.hpp"


Player::Player(Camera& camera)
: camera{camera}, HP{100}, Points{0}, scale{0.5f}
{
    // this->position = new GLfloat[3]{0.0f, 100.0f, 5.0f};
    this->position = {2.0f, 1.0f, 1.0f};

    this->shader = loadShaders("shader/player.vert", "shader/player.frag");
    this->scaleMatrix = S(scale);
    this->rotationMatrix = Rx(4.7f); //IdentityMatrix();
    
    this->numVertices = 3 * 3 * 6;
    
    unsigned int vertexBufferObjID;
	unsigned int fragmentBufferObjID;

    this->pyramidVertices = new GLfloat[3*18]{
    
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,

        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,


    //
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,

        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,

        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,

        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f};

    

    this->colors = new GLfloat[3*3]
        {
            0.5f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.0f, 0.0f, 0.5f};
    // Allocate and activate Vertex Array Object
    glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);

    // Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);

    // VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));

    // VBO for vertex data
	glGenBuffers(1, &fragmentBufferObjID);

	glBindBuffer(GL_ARRAY_BUFFER, fragmentBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), colors, GL_STATIC_DRAW);
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


void Player::Update()
{
    ;
}


void Player::Draw()
{
    glUseProgram(shader);
  
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_TRUE, this->camera.GetViewMatrix());
    glUniformMatrix4fv(glGetUniformLocation(shader, "rotationMatrix"), 1, GL_TRUE, this->rotationMatrix.m);
    glUniformMatrix4fv(glGetUniformLocation(shader, "transformationMatrix"), 1, GL_TRUE, T(position.x, position.y, position.z).m);



    glBindVertexArray(vertexArrayObjID); // Select VAO
	glDrawArrays(GL_TRIANGLES, 0, numVertices / 3);	 // draw object
}

void Player::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    this->position.x = x;
    this->position.y = y; // We may not want to change the y-value here
    this->position.z = z;
}