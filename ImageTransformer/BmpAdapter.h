#pragma once
#include "Adapter.h"
#include "Pixel.h"
#include <memory>


class BmpAdapter :
	public Adapter
{
public:
	std::unique_ptr<Data> Adapt(std::vector<unsigned char>& data);

private:
	std::unique_ptr<Data> LoadPixels(std::vector<unsigned char>& rawdata, const BmpHeaderInfo* header); //can only pass unique by ref or by func(move(ptr))
	Pixel BuildBmpPixel(std::vector<unsigned char>& rawdata, const int pixelLength, int idx);
	const int GetPadding(uint32_t bitsPerPixel, uint32_t width);
	const int GetPixelLength(const int bitsPerPixel);
};

