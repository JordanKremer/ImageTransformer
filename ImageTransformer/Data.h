#pragma once
#include <vector>
#include <memory>
#include "HeaderInfo.h"
#include "BmpHeaderInfo.h"
#include "Pixel.h"

class Data
{
public:
	Data();
	Data(std::vector<unsigned char> &data, std::vector<Pixel>& pixels, const HeaderInfo* header);
	
	_NODISCARD const int GetCompression();


private:
	HeaderInfo* _header; //may change to unique ptr
	std::vector<unsigned char> _rawData; //may not need this
	std::vector<Pixel> _pixels;

};

