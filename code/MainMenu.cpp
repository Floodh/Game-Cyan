#include "MainMenu.hpp"



MainMenu::MainMenu()
{
    Rect area{0,0,200,125};
    Button playButton{area, true, true, new GLfloat[3]{0.5f, 0.2f, 0.6f}};
        area.y += area.height + 50;
        area.x += 50;
        Button map1Button{area, false, false, new GLfloat[3]{0.5f, 0.2f, 0.6f}};

    //  y stays the same until the play button is pressed
    area.x -= 50;
    Button quitButton{area, true, true, new GLfloat[3]{0.5f, 0.2f, 0.6f}};




    //  we will initlize the variables for drawing rectangles here

    this->shader = loadShaders("shader/rect.vert", "shader/rect.frag");

    this->indexCount = 3 * 2;
    this->vertexCount = 4;
    this->valueCount = this->vertexCount * 3;

    this->indices = new GLint[this->indexCount];
    this->vertices = new GLfloat[this->valueCount];


    glGenVertexArrays(1, &vertexArrayObjID);

    glGenBuffers(1, &indexBufferObjID);
    glGenBuffers(1, &vertexBufferObjID);


    glBindVertexArray(vertexArrayObjID);

    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shader, "inPosition"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLuint), indices, GL_STATIC_DRAW);

}

void MainMenu::Update()
{
    //
}

void MainMenu::Draw()
{
    DrawButton(playButton);
        DrawButton(map1Button);
    DrawButton(quitButton);



}

void MainMenu::DrawButton(const Button& button)
{
    if (button.visible)
        this->DrawRect(button.area, button.color);
}



void MainMenu::DrawRect(const Rect rect, GLfloat* color)
{

    //  set the color of the rectangle
    glUniform3fv(glGetUniformLocation(shader, "eyePosition"), 1, color);

    //  set the 4 points
        this->vertices[0] = rect.x;
        this->vertices[1] = rect.y;
        this->vertices[2] = 0;

        this->vertices[3] = rect.x + rect.width;
        this->vertices[4] = rect.y;
        this->vertices[5] = 0;

        this->vertices[6] = rect.x + rect.width;
        this->vertices[7] = rect.y + rect.height;
        this->vertices[8] = 0;

        this->vertices[9] = rect.x;
        this->vertices[10] = rect.y  + rect.height;
        this->vertices[11] = 0;

    //  update the stuff
	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(shader, "inPosition"));

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0L);
}