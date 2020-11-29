/*
Author : Jordan Kremer
11/20/20
Loader.cpp

The only functionality of this class is to load byte values from a selected
file and return that data to the class it interacts with.

*/

#include "Loader.h"
#include <fstream>


Loader::Loader() {}


std::vector<unsigned char>& Loader::Load(std::string filename)
{

	std::ifstream in;

	in.open(filename, std::ios::binary);

	//exception is throw when using a loop with while(!in.eof), so using a range based for loop instead
	in.exceptions(in.failbit);

	//Go to end of file, get byte number, go back to beginning of file
	in.seekg(0, in.end);
	int fileLength = in.tellg();
	in.seekg(0, in.beg);

	unsigned char dataByte;
	std::vector<unsigned char> loadData;

	int reserveAmount = 2 * fileLength;
	loadData.reserve(reserveAmount);
	
	for (int i = 0; i < fileLength; ++i)
	{
		in.read((char*)& dataByte, 1);
		loadData.push_back(dataByte);
	}
	in.close();

	return loadData;
}


