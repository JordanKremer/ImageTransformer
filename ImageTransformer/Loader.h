#pragma once
#include "Data.h"
#include <string>
#include <vector>
class Loader
{
//	std::string getFileName() const;
public:
	Loader();
	std::vector<unsigned char>& Load(std::string filename);

private:
	//std::vector<unsigned char> _rawData;
	//std::string _fileName;
};

