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
            cout << value[(i * width) + j] << ' ';
        cout << endl;
    }
}

void Console::WriteLine(unsigned int* value, const int width, const int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << value[(i * width) + j] << ' ';
        cout << endl;
    }
}

void Console::WriteLine(uint8_t* value, const int width, const int height, const int groupSize)
{
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * groupSize; j++)
        {
            if (count % 4 == 0)
                cout << "( ";
            cout << (unsigned int)value[(i * width * groupSize) + j] << ' ';
            if (count++ % 4 == 3)
                cout << ") ";
        }
        cout << endl;
    }
}