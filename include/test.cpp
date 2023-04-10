#include "GL_utilities.h"
#include "LoadBMP.hpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

#include <iostream>

using namespace std;


int main()
{
    char const* fname = "../data/level/lena.bmp";
    int width, height, channel;
    GLfloat* test;
    // float* test;
    // FILE *f = stbi__fopen(fname, "rb");

    // if (!f)
    //     cout << "test" << endl;
    // else
    //     cout << "hej" << endl;

    test = LoadBMP(fname, width, height, channel);
    // cout << test << endl;

    cout << sizeof(test) << endl;

    int c{};

    for (int i=0;i<120000;i++)
    {
        cout << "Index: " << i << " innehåller: " << test[i] << endl;
        
        if (c == 2)
        {
            cout << endl;
            c = 0;
        }
        else
            c++;

    }
    
    return 0;
}