/*
Author : Jordan Kremer
11/20/20
Loader.h

The only functionality of this class is to load byte values from a selected
file and return that data to the class it interacts with.

*/


#pragma once
#include <string>
#include <vector>
class Loader
{
public:
	Loader();
	//vector just moves the data, it won't copy it
	//no need to pass by ref or return by ref
	std::vector<unsigned char> Load(std::string filename);
};

