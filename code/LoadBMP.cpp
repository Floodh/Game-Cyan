#include "LoadBMP.hpp"


#include <iostream>
#include <fstream> 
#include <string> 

using namespace std;

//  http://echachik.blogspot.com/2014/09/bmp-c.html
uint8_t* LoadBMP(char const *path, int& outWidth, int& outHeight)
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

	if ( bits_per_pixel != 32 )
        return NULL;

    //  allocate memory
    uint8_t* pixelData = new uint8_t[width * height * 4];


    //  read the raw file data, conveniently its already in the format we wan't
    file.read ((char*)pixelData, height * width * 4);

	
	for (int i=0; i < (width * height * 4); i+=4)
	{
		uint8_t tmp = pixelData[i];
		pixelData[i] = pixelData[i+2];
		pixelData[i+2] = tmp;
	}

	outWidth = width;
	outHeight = height;
    return pixelData;

}


