#include<opencv2/opencv.hpp>
#include<iostream>
#include "BmpLoader.h"
#include "Data.h"


using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	/*
#ifdef
	
#else
	std::string FILENAME = argv[1];

	*/

	std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp";

	Loader _loader;

	std::vector<unsigned char>& _data = _loader.Load(FILENAME);


	//MAKE TRANSFORMATION FUNCTIONS AS TEMPLATES
}