#pragma once
#include "Pixel.h"
class PixelFactory
{
public:
	Pixel& GetPixel(int bitsPerPixel, std::vector<unsigned char>& data, int dataIdx);
};

