/*
Author : Jordan Kremer
11/20/20
BmpAdapter.h

Adapts unsigned char byte vector values to a GenericImage object with a BmpHeader and Pixel vector. Adapts from a GenericImage
object to unsigned char byte vector values to be written to file.
*/

#pragma once
#include "Adapter.h"
#include "Pixel.h"
#include <memory>


class BmpAdapter :
	public Adapter
{
public:
	std::unique_ptr<GenericImage> AdaptFromRaw(std::vector<unsigned char>& data);
	const std::vector<unsigned char> AdaptToRaw(std::unique_ptr<GenericImage> data);

private:
	std::unique_ptr<GenericImage> LoadPixels(std::vector<unsigned char>& rawdata, std::unique_ptr<BmpHeaderInfo> header); //can only pass unique by ref or by func(move(ptr))
	Pixel BuildBmpPixel(std::vector<unsigned char>& rawdata, const int pixelLength, int idx);
	//Padding are the extra bytes at the end of a line to make sure the horizontal line fits the bmp format
	const int GetPadding(uint32_t bitsPerPixel, uint32_t width);
	//Channels are color channels within the Pixel, e.g. a 32bit bmp pixel will have 4 channels (RGBA)
	const int GetChannelCount(const int bitsPerPixel);
	
};
