#include "PixelFactory.h"

Pixel& PixelFactory::GetPixel(int channelCount, std::vector<unsigned char>& data, int dataIdx)
{

	std::vector<unsigned char> channelData;
	

	if (channelCount == 1 || channelCount == 4) {
		channelData.push_back(data[dataIdx]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if (channelCount == 8)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if(channelCount == 16 || channelCount == 24)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else if (channelCount == 32)
	{
		channelData.push_back(data[dataIdx]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		channelData.push_back(data[dataIdx++]);
		Pixel pixel(channelData, channelCount);
		return pixel;
	}
	else {
		throw std::runtime_error("ERROR: PIXELFACTORY: channelCount OUT OF BOUNDS");
	}
}
