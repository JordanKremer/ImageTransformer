#pragma once
#include "Data.h"
#include <string>
#include <vector>
class Loader
{
	std::string getFileName() const;
	std::vector<unsigned char>& load();

private:
	std::vector<unsigned char> _rawData;
	std::string _fileName;
};

