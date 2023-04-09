#include "Console.hpp"

using namespace std;

void Console::WriteLine(string const& content)
{
    cout << content << endl;
}

void Console::WriteLine(GLfloat* value, const int size)
{
    for (int i = 0; i < size; i++)
        cout << value[i] << " ";
    cout << endl;
}

void Console::WriteLine(GLfloat* value, const int width, const int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << value[(i * width) + j];
        cout << endl;
    }
}
