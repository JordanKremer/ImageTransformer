/*
Author : Jordan Kremer
1/24/2021
writer.h

Includes functionality to write a byte vector to disk.
*/

#pragma once
#include <vector>
#include <string>

class writer
{
public:
	static void write_to_file(std::vector<unsigned char> raw_image_values, const std::string filename);
};

