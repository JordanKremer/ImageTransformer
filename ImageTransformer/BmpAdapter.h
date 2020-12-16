/*
Author : Jordan Kremer
11/20/20
BmpAdapter.h

Adapts rawData to a Data object with a BmpHeader and Pixel vector. Adapts from a Data
object to rawData, so that the rawData may be written to file.
*/

#pragma once
#include "Adapter.h"
#include "Pixel.h"
#include <memory>


class BmpAdapter :
	public Adapter
{
public:
	std::unique_ptr<Data> AdaptFromRaw(std::vector<unsigned char>& data);
	const std::vector<unsigned char> AdaptToRaw(std::unique_ptr<Data> data);


private:
	std::unique_ptr<Data> LoadPixels(std::vector<unsigned char>& rawdata, std::unique_ptr<BmpHeaderInfo> header); //can only pass unique by ref or by func(move(ptr))
	Pixel BuildBmpPixel(std::vector<unsigned char>& rawdata, const int pixelLength, int idx);
	const int GetPadding(uint32_t bitsPerPixel, uint32_t width);
	const int GetChannelCount(const int bitsPerPixel);
	
};
