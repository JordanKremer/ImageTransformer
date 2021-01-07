#pragma once
#include <vector>
#include <string>
#include <fstream>
class Writer
{
	void WriteToFile(std::vector<unsigned char> rawImageData, const std::string FILENAME);
};

