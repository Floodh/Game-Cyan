#include "MainMenu.hpp"


#include <iostream>
using namespace std;


#define BUTTONWIDTH 250
#define BUTTONHEIGHT 150
#define BUTTONSPACING_X 50
#define BUTTONSPACING_Y 25


MainMenu::MainMenu(const int & windowWidth, const int & windowHeight, Mouse& mouse)
    : windowWidth(windowWidth), windowHeight(windowHeight), mouse{mouse}
{
    unsigned int assignedIndexes = 0;

    Rect area{(windowWidth - BUTTONWIDTH) / 2, BUTTONHEIGHT + BUTTONSPACING_Y, BUTTONWIDTH, BUTTONHEIGHT};
    this->playButton = Button{area, true, true, new GLfloat[3]{0.5f, 0.2f, 0.6f}, assignedIndexes++};
        area.y += area.height + BUTTONSPACING_Y;
        area.x += BUTTONSPACING_X;
        this->map1Button = Button{area, false, false, new GLfloat[3]{0.5f, 0.2f, 0.6f}, assignedIndexes++};

    //  y stays the same until the play button is pressed
    area.x -= BUTTONSPACING_X;
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
    if (mouse.left.keydown)
    {
        this->mouseDownX = mouse.x;
        this->mouseDownY = mouse.y;
    }

    //  when we let the mouse button go, that's when we check if we picked an option
    if (mouse.left.keyup)
    {
        // cout << "Update" << endl;
        // cout << "       response = " << response << endl;
        // cout << "       loadMap = " << loadMap << endl;   

        // cout << "       Mouse:" << endl;
        // cout << "           downX = " << mouseDownX << ", downY = " << mouseDownY << endl;  
        // cout << "           upX = " << mouse.x << ", upY = " << mouse.y << endl;      
        if (IsSelectedButton(playButton))
        {
            if (playButton.clicked == false)
            {
                playButton.clicked = true;
                this->response = MainMenu_Play;
                this->quitButton.area.y += BUTTONHEIGHT + BUTTONSPACING_Y;
                this->map1Button.visible = true;
                this->map1Button.enabled = true;
            }
            else
            {
                playButton.clicked = false;
                this->response = MainMenu_None;
                this->quitButton.area.y -= BUTTONHEIGHT + BUTTONSPACING_Y;
                this->map1Button.visible = false;
                this->map1Button.enabled = false;
            }
        }
        else if (IsSelectedButton(map1Button))
        {
            this->response = MainMenu_Load;
            this->loadMap = 1;  //  hardcoded for now
        }
        else if (IsSelectedButton(quitButton))
        {
            this->response = MainMenu_Quit;
        }
    }


    
}

void MainMenu::Draw()
{

    //cout << "Drawing main menu:" << endl;


    glDisable(GL_DEPTH_TEST);

    DrawButton(playButton);
        DrawButton(map1Button);
    DrawButton(quitButton);

    glEnable(GL_DEPTH_TEST);



}

void MainMenu::DrawButton(const Button& button)
{
    //cout << "     Drawing button: visable = " << button.visible << endl;
    if (button.visible)
        this->DrawRect(button.area, button.color);
}

bool MainMenu::IsSelectedButton(const Button& button)
{
    if (button.visible == false)
        return false;
    if (button.enabled == false)
        return false;

    // cout << "1, " << (this->mouseDownX >= button.area.x) << ", " << (this->mouseDownX <= button.area.x + button.area.width) << endl;
    // cout << "   mouse down.x = " << this->mouseDownX << ", area.x =" << button.area.x << endl;
    //  if the down is inside the area
    if (this->mouseDownX >= button.area.x && this->mouseDownX <= button.area.x + button.area.width)
    if (this->mouseDownY >= button.area.y && this->mouseDownY <= button.area.y + button.area.height)
    //  if the up is also inside the area
    if (mouse.x >= button.area.x && mouse.x <= button.area.x + button.area.width)
    if (mouse.y >= button.area.y && mouse.y <= button.area.y + button.area.height)
        return true;



    return false;

}

//  not very optimized, like at all
void MainMenu::DrawRect(const Rect rect, GLfloat* color)
{

    // cout << "          Drawing rect" << endl;
    // cout << "               x = " << rect.x << ", y = " << rect.y << endl;
    // cout << "               width = " << rect.width << ", height = " << rect.height << endl;

    glUseProgram(shader);
    //  set the color of the rectangle
    glUniform3fv(glGetUniformLocation(shader, "rectColor"), 1, color);

    //  set the 4 points
        this->vertices[0] = (GLfloat)( rect.x) / (windowWidth / 2) - 1.0f;
        this->vertices[1] = (GLfloat)( -rect.y) / (windowHeight / 2) + 1.0f;
        this->vertices[2] = 0.0f;

        this->vertices[3] = (GLfloat)(+ rect.x + rect.width) / (windowWidth / 2) - 1.0f;
        this->vertices[4] = (GLfloat)( - rect.y) / (windowHeight / 2) + 1.0f;
        this->vertices[5] = 0.0f;

        this->vertices[6] = (GLfloat)( + rect.x + rect.width) / (windowWidth / 2) - 1.0f;
        this->vertices[7] = (GLfloat)( - rect.y - rect.height) / (windowHeight / 2) + 1.0f;
        this->vertices[8] = 0.0f;

        this->vertices[9] = (GLfloat)( + rect.x) / (windowWidth / 2) - 1.0f;
        this->vertices[10] = (GLfloat)(- rect.y - rect.height) / (windowHeight / 2) + 1.0f;
        this->vertices[11] = 0.0f;


    //  update the stuff
	glBindVertexArray(this->vertexArrayObjID);    // Select VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, this->vertexCount*3*sizeof(GLfloat), this->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(this->shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(glGetAttribLocation(this->shader, "inPosition"));


    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0L);
}