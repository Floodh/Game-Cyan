#include "VertexShape.hpp"

//  help data type
struct Point 
{
    Point(GLfloat x, GLfloat y, GLfloat z)
        : x(x), y(y), z(z)
    {}
    GLfloat x, y, z;
};


VertexShape VertexShape_Diamond(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat ratio)
{
    VertexShape shape{};


    Point top   {x, y + size * ratio, z};

    Point mid0  {x + size,  y,          z       };
    Point mid1  {x,         y,          z + size};
    Point mid2  {x - size,  y,          z       };
    Point mid3  {x,         y,          z - size};

    Point bot   {x, y - size * ratio, z};
    

    shape.indexCount = 8;
    shape.vertexCount = 6;
    shape.valueCount = shape.vertexCount * 3;

    shape.indices = new GLint[shape.indexCount]
    {   
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,1,

        5,1,2,
        5,2,3,
        5,3,4,
        5,4,1
    };

    shape.vertices = new GLfloat[shape.valueCount]
    {
        top.x, top.y, top.z,
        mid0.x, mid0.y, mid0.z,
        mid1.x, mid1.y, mid1.z,
        mid2.x, mid2.y, mid2.z,
        mid3.x, mid3.y, mid3.z,
        bot.x, bot.y, bot.z
    };

    shape.colors = new GLfloat[shape.valueCount];
    //  we let the user decide these colors


    //  create data for rendering
    glGenVertexArrays(1, &shape.vertexArrayObjID);


    glGenBuffers(1, &shape.indexBufferObjID);
    glGenBuffers(1, &shape.vertexBufferObjID);
    glGenBuffers(1, &shape.colorBufferObjID);

    return shape;


    // glBindVertexArray(shape.vertexArrayObjID);

    // glBindBuffer(GL_ARRAY_BUFFER, shape.vertexBufferObjID);
    // glBufferData(GL_ARRAY_BUFFER, shape.vertexCount*3*sizeof(GLfloat), shape.vertices, GL_STATIC_DRAW);
    // glVertexAttribPointer(glGetAttribLocation(shape.shader, "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    // glEnableVertexAttribArray(glGetAttribLocation(shape.shader, "inPosition"));	 

    // glBindBuffer(GL_ARRAY_BUFFER, shape.colorBufferObjID);
    // glBufferData(GL_ARRAY_BUFFER, shape.ertexCount*3*sizeof(GLfloat), shape.colors, GL_STATIC_DRAW);
    // glVertexAttribPointer(glGetAttribLocation(shape.shader, "inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
    // glEnableVertexAttribArray(glGetAttribLocation(shape.shader, "inColor"));

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferObjID);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexCount*sizeof(GLuint), shape.indices, GL_STATIC_DRAW);    

    // glUniformMatrix4fv(glGetUniformLocation(shape.shader, "projectionMatrix"), 1, GL_TRUE, this->camera.GetProjectionMatrix());
    // glUniform3fv(glGetUniformLocation(shape.shader, "eyePosition"), 1, this->camera.position);


}