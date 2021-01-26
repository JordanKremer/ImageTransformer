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
	static std::vector<unsigned char> load(const std::string& filename);
};

