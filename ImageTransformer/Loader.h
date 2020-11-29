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
	std::vector<unsigned char>& Load(std::string filename);
};

