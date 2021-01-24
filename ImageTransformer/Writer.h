/*
Author : Jordan Kremer
1/24/2021
Writer.h

Includes functionality to write a byte vector to disk.
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>

class Writer
{
public:
	void WriteToFile(std::vector<unsigned char> rawImageData, const std::string FILENAME);
};

