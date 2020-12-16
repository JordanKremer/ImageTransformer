/*
Author : Jordan Kremer
11/20/20
BmpAdapter.cpp

Adapts rawData to a Data object with a BmpHeader and Pixel vector. Adapts from a Data
object to rawData, so that the rawData may be written to file.
*/


#include "BmpAdapter.h"
#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_32Bit.h"
#include <memory>
#include <stdexcept>


//Takes a byte vector and builds a Data object with a BmpHeader and Pixel vector
std::unique_ptr<Data> BmpAdapter::AdaptFromRaw(std::vector<unsigned char>& data)
{
	if (!(data[0] == 'B' && data[1] == 'M'))
	{
		throw std::runtime_error("ERROR: NOT A BMP");
	}

	if (data.size() < 54)
	{
		throw std::runtime_error("ERROR: HEADER TOO SMALL");
	}

	BmpHeaderFactory fac;
	auto bmpHeader = fac.GetBmpHeader(data);
	uint32_t compression = bmpHeader->GetCompression();
	uint32_t bitsPerPixel = bmpHeader->GetBitsPerPixel();

	return LoadPixels(data, std::move(bmpHeader));
}



//Adapts image data to raw format, by calling BuildRawDataVector
//to concat and return the header and pixels
//either pass by ref or use move to pass the unique ptr in
const std::vector<unsigned char> BmpAdapter::AdaptToRaw(std::unique_ptr<Data> data)
{
	auto header = data->GetHeader();
	auto pixels = data->GetPixels();
	if (pixels.size() == 0)
	{
		throw std::runtime_error("ERROR: Pixel vector has no data");
	}

	std::vector<unsigned char> rawData;
	const int pixelChannelCount = pixels[0].GetChannelCount();
	int reserveSize = header.size() + (pixelChannelCount * pixels.size());
	rawData.reserve(reserveSize);

	for (auto& x : header)
	{
		rawData.push_back(x);
	}

	//there may be a faster method, possibly by parallelizing
	for (auto& pixel : pixels) {
		for (auto& channel : pixel.GetAllChannelData()) {
			rawData.push_back(channel);
		}
	}

	return rawData;
}



//Load pixels from raw data vector into a vector of pixels, taking head of the line padding
//unique ptrs must be passed by ref or by func(move(ptr))
std::unique_ptr<Data> BmpAdapter::LoadPixels(std::vector<unsigned char>& rawdata, std::unique_ptr<BmpHeaderInfo> header)
{
	std::vector<Pixel> pixelData;
	pixelData.reserve(int64_t(header->GetWidth()) * header->GetHeight()); 	//cast to 8 byte to avoid overflow

	const int padding = GetPadding(header->GetBitsPerPixel(), header->GetWidth());
	const int startOfImage = header->GetImageStartOffset();
	const int channelCount = GetChannelCount(header->GetBitsPerPixel());
	const int bitsPerLine = header->GetBitsPerPixel() * header->GetWidth();
	int bitCount = 0;

	for(int idx = startOfImage; idx < rawdata.size(); idx += channelCount)
	{
		//if we are at the end of the line, ignore the padding
		if (bitCount == bitsPerLine)
		{
			idx += padding;
			if (idx >= rawdata.size()-1) //maybe minus 1
				break;
			bitCount = 0;
		}

		pixelData.push_back(BuildBmpPixel(rawdata, channelCount, idx));
		bitCount += channelCount;
	}

	return std::move(std::make_unique<Data>(rawdata, pixelData, std::move(header)));
}



//Bmp pixels are just byte vectors, so creating a bmp pixel is simply reading
//how many channels the bmp image has in the given format by reading the header
//and building a pixel container from the rawdata
Pixel BmpAdapter::BuildBmpPixel(std::vector<unsigned char>& rawdata, const int channelCount, int idx)
{
	std::vector<unsigned char> pixelChannelData;
	for (int x = 0; x < channelCount; ++x)
	{
		//build our pixel
		pixelChannelData.push_back(rawdata[idx + x]);
	}
	Pixel pixel(pixelChannelData, channelCount);
	return pixel;
}



//Padding is the left over bits required at the end of each line in a bmp image,
//when reading and writing they must be taken into account
const int BmpAdapter::GetPadding(uint32_t bitsPerPixel, uint32_t width)
{
	return ((width * bitsPerPixel) % 32) / 8;
}



//Each Bmp format will have a different number of pixels, refer to
//the wiki for more information
const int BmpAdapter::GetChannelCount(const int bitsPerPixel)
{
	if (bitsPerPixel == 1 || bitsPerPixel == 4)
		return 1;
	else if (bitsPerPixel == 8)
		return 2;
	else if (bitsPerPixel == 16 || bitsPerPixel == 24)
		return 3;
	else if (bitsPerPixel == 32)
		return 4;
	else
		throw std::runtime_error("ERROR: bitsPerPixel OUT OF BOUNDS in GetPixelLength()");
}


