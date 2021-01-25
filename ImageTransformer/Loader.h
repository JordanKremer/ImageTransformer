/*
Author : Jordan Kremer
11/20/20
loader.h

The only functionality of this class is to load byte values from a selected
file and return that data to the class it interacts with.

*/


#pragma once
#include <string>
#include <vector>
class loader
{
public:
	loader();
	//vector just moves the data, it won't copy it
	//no need to pass by ref or return by ref
	std::vector<unsigned char> load(std::string filename);
};

