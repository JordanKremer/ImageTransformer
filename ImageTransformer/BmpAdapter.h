#pragma once
#include "Adapter.h"
#include "Pixel.h"
#include <memory>


class BmpAdapter :
	public Adapter
{
public:
	std::unique_ptr<Data> AdaptFromRaw(std::vector<unsigned char>& data);
	std::vector<unsigned char> AdapterToRaw(std::unique_ptr<Data> data);
private:
	std::unique_ptr<Data> LoadPixels(std::vector<unsigned char>& rawdata, const BmpHeaderInfo* header); //can only pass unique by ref or by func(move(ptr))
	Pixel BuildBmpPixel(std::vector<unsigned char>& rawdata, const int pixelLength, int idx);
	const int GetPadding(uint32_t bitsPerPixel, uint32_t width);
	const int GetPixelLength(const int bitsPerPixel);
};

