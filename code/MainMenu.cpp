#include "MainMenu.hpp"


#include <iostream>
using namespace std;


#define BUTTONWIDTH 450
#define BUTTONHEIGHT 200
#define BUTTONSPACING 100


MainMenu::MainMenu(const int & windowWidth, const int & windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight)
{
    unsigned int assignedIndexes = 0;

    Rect area{(windowWidth + BUTTONWIDTH) / 2, BUTTONHEIGHT + BUTTONSPACING, BUTTONWIDTH, BUTTONHEIGHT};
    this->playButton = Button{area, true, true, new GLfloat[3]{0.5f, 0.2f, 0.6f}, assignedIndexes++};
        area.y += area.height + BUTTONSPACING;
        area.x += BUTTONSPACING;
        this->map1Button = Button{area, false, false, new GLfloat[3]{0.5f, 0.2f, 0.6f}, assignedIndexes++};

    //  y stays the same until the play button is pressed
    area.x -= BUTTONSPACING;
    this->quitButton = Button{area, true, true, new GLfloat[3]{0.5f, 0.2f, 0.6f}, assignedIndexes++};




    //  we will initlize the variables for drawing rectangles here

    this->shader = loadShaders("shader/rect.vert", "shader/rect.frag");

    this->indexCount = 3 * 2;
    this->vertexCount = 4;
    this->valueCount = this->vertexCount * 3;

    this->indices = new GLint[this->indexCount] {0,1,2, 2,3,0};
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

    cout << "Drawing main menu:" << endl;


    glDisable(GL_DEPTH_TEST);

    DrawButton(playButton);
        DrawButton(map1Button);
    DrawButton(quitButton);

    glEnable(GL_DEPTH_TEST);



}

void MainMenu::DrawButton(const Button& button)
{
    cout << "     Drawing button: visable = " << button.visible << endl;
    if (button.visible)
        this->DrawRect(button.area, button.color);
}

//  not very optimized, like at all
void MainMenu::DrawRect(const Rect rect, GLfloat* color)
{

    cout << "          Drawing rect" << endl;
    cout << "               x = " << rect.x << ", y = " << rect.y << endl;
    cout << "               width = " << rect.width << ", height = " << rect.height << endl;

    glUseProgram(shader);
    //  set the color of the rectangle
    glUniform3fv(glGetUniformLocation(shader, "rectColor"), 1, color);

    //  set the 4 points
        this->vertices[0] = (GLfloat)(-windowWidth + rect.x) / windowWidth;
        this->vertices[1] = (GLfloat)(windowHeight - rect.y) / windowHeight;
        this->vertices[2] = 0.0f;

        this->vertices[3] = (GLfloat)(-windowWidth + rect.x + rect.width) / windowWidth;
        this->vertices[4] = (GLfloat)(windowHeight - rect.y) / windowHeight;
        this->vertices[5] = 0.0f;

        this->vertices[6] = (GLfloat)(-windowWidth + rect.x + rect.width) / windowWidth;
        this->vertices[7] = (GLfloat)(windowHeight - rect.y - rect.height) / windowHeight;
        this->vertices[8] = 0.0f;

        this->vertices[9] = (GLfloat)(-windowWidth + rect.x) / windowWidth;
        this->vertices[10] = (GLfloat)(windowHeight - rect.y - rect.height) / windowHeight;
        this->vertices[11] = 0.0f;


    //  update the stuff
	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, this->vertexCount*3*sizeof(GLfloat), this->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));


    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0L);
}