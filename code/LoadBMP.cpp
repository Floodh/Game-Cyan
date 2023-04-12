#include "LoadBMP.hpp"


#include <iostream>
#include <fstream> 
#include <string> 

using namespace std;

//  http://echachik.blogspot.com/2014/09/bmp-c.html
uint8_t* LoadBMP(char const *path, int& outWidth, int& outHeight, int& channels)
{
    int size = 0, pixels_adress = 0, width = 0, height = 0;
	short int bits_per_pixel = 0;


	ifstream file (path, ios::in | ios::binary);

	file.seekg( 2, ios::beg);

	file.read ((char*)&size, sizeof(int));
	////////////////////////////////////////////////////

	file.seekg( 10, ios::beg);

	file.read ((char*)&pixels_adress, sizeof(int));
	//////////////////////////////////////////////////////

	file.seekg( 18, ios::beg);

	file.read ((char*)&width, sizeof(int));

	file.read ((char*)&height, sizeof(int));
	/////////////////////////////////////////////////////


	file.seekg( 28, ios::beg);

	file.read ((char*)&bits_per_pixel, sizeof(short int));

	/////////////////////////////////////////////////////////

	file.seekg( pixels_adress, ios::beg);



	cout << "Size: " << size << endl;
	cout << "pixels_adress: " << pixels_adress << endl;
	cout << "bits per pixel: " << bits_per_pixel << endl;
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;

    unsigned int* pixels = new unsigned int[width * height];

	if ( bits_per_pixel != 32 )
        return NULL;
	

    unsigned int bgr;
    for( int y = 0; y < height; y++)    //  consider inverting this
    {
        for( int x = 0; x < width; x++)
        {
            std::cout << " " << x << " " << y << std::endl;
            file.read ((char*)&bgr, 4); 
            pixels[x + y * width] = bgr;
        }
    }

    uint8_t* recastedResult = (uint8_t*)(pixels);
    for (int i = 0; i < width * height * 4; i++)
        std::cout << "at i = " << i << " gives " <<  (unsigned int)recastedResult[i] << std::endl;

    return recastedResult;

}