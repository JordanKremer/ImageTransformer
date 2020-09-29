#include "PixelFactory.h"

Pixel& PixelFactory::GetPixel(int bitsPerPixel, std::vector<unsigned char>& data, int dataIdx)
{

	std::vector<unsigned char> channelData;
	

	if (bitsPerPixel == 1 || bitsPerPixel == 4) {
		channelData.push_back(data[dataIdx]);
		Pixel pixel(channelData);
		return pixel;
	}
	else if (bitsPerPixel == 8)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData);
		return pixel;
	}
	else if(bitsPerPixel == 16 || bitsPerPixel == 24)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData);
		return pixel;
	}
	else if (bitsPerPixel == 32)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData);
		return pixel;
	}
	else {
		throw std::runtime_error("ERROR: PIXELFACTORY: bitsPerPixel OUT OF BOUNDS");
	}
}
