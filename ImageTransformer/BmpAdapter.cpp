#include "BmpAdapter.h"
#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"
#include <memory>
#include <stdexcept>



std::unique_ptr<Data> BmpAdapter::AdaptFromRaw(std::vector<unsigned char>& data)
{
	//Build new data object with a header and the raw data

	//first send a cut of the vector to the bmpheader contructor
	//but find out which bmpheader we need first, somehow 

	if (!(data[0] == 'B' && data[1] == 'M'))
	{
		throw std::runtime_error("ERROR: NOT A BMP");
	}

	//std::vector<unsigned char> _rawData;

	BmpHeaderFactory fac;

	//cannot do this as it is trying to assign a unique ptr to something else
	//auto bmpHeader = fac.getBmpHeader(data);	

	//move it instead
	auto bmpHeader = fac.GetBmpHeader(data);
	uint32_t compression = bmpHeader->GetCompression();
	uint32_t bitsPerPixel = bmpHeader->GetBitsPerPixel();

	//causes symbol load error, workaround by returning unique_ptr in loadpixel
	//instead of a vector<pixel>&
	//std::vector<Pixel> pixelData = LoadPixels(data, bmpHeader);

	return LoadPixels(data, bmpHeader);
}


//Load pixels from raw data vector into a vector of pixels, taking head of the line padding
//unique ptrs must be passed by ref or by func(move(ptr))
std::unique_ptr<Data> BmpAdapter::LoadPixels(std::vector<unsigned char>& rawdata, const BmpHeaderInfo* header)
{
	std::vector<Pixel> pixelData;
	//cast to 8 byte to avoid overflow
	pixelData.reserve(int64_t(header->GetWidth()) * header->GetHeight());

	const int padding = GetPadding(header->GetBitsPerPixel(), header->GetWidth());
	const int startOfImage = header->GetImageStartOffset();
	const int pixelLength = GetPixelLength(header->GetBitsPerPixel());
	const int bitsPerLine = header->GetBitsPerPixel() * header->GetWidth();
	int bitCount = 0;

	for(int idx = startOfImage; idx < rawdata.size(); idx += pixelLength)
	{
		//if we are at the end of the line, ignore the padding
		if (bitCount == bitsPerLine)
		{
			idx += padding;
			if (idx >= rawdata.size()-1) //maybe minus 1
				break;
			bitCount = 0;
		}

		pixelData.push_back(BuildBmpPixel(rawdata, pixelLength, idx));
		bitCount += pixelLength;
	}

	return std::make_unique<Data>(rawdata, pixelData, header);
}




Pixel BmpAdapter::BuildBmpPixel(std::vector<unsigned char>& rawdata, const int pixelLength, int idx)
{
	std::vector<unsigned char> pixelChannelData;
	for (int x = 0; x < pixelLength; ++x)
	{
		//build our pixel
		pixelChannelData.push_back(rawdata[idx + x]);
	}
	Pixel pixel(pixelChannelData);
	return pixel;
}



const int BmpAdapter::GetPadding(uint32_t bitsPerPixel, uint32_t width)
{
	return ((width * bitsPerPixel) % 32) / 8;
}



const int BmpAdapter::GetPixelLength(const int bitsPerPixel)
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




