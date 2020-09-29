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
	Data(std::vector<unsigned char> &data, std::vector<Pixel>& pixels, std::unique_ptr<HeaderInfo> header);
	_NODISCARD const int GetCompression();


private:
	std::unique_ptr<HeaderInfo> _header;
	std::vector<unsigned char> _rawData;
	std::vector<Pixel> _pixels;

};

