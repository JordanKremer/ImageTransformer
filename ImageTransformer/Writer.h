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

