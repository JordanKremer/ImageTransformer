#include "GreyScale.h"

std::vector<Pixel> GreyScale::TransformPixels(std::vector<Pixel> pixels)
{
	auto Width = GetHeader()->GetWidth();
	auto Height = GetHeader()->GetHeight();

	for (uint32_t x = 0; x < Width; x++)
	{
		for (uint32_t y = 0; y < Height; y++)
		{
			SetPixelGrey(pixels[GetCoordinate(x, y)]);
		}
	}

	return pixels;
}

std::unique_ptr<HeaderInfo> GreyScale::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
    //No op
    return std::move(hdr);
}




//Averages byte color values and sets pixel to color.
void GreyScale::SetPixelGrey(Pixel& toGrey)
{
	uint8_t averageChannelValue = AverageRGBValues(toGrey.GetAllChannelData());
	int channelIdx = 0;
	for (auto& channelValue : toGrey.GetAllChannelData())
	{
		toGrey.SetChannel(channelIdx, averageChannelValue);
		++channelIdx;
	}
}



//Averages the channel byte data for a given pixel
//and returns that number.
uint8_t GreyScale::AverageRGBValues(const std::vector<unsigned char> channels)
{
	int averageChannelValue = 0;
	for (int channelIdx = 0; channelIdx < channels.size(); ++channelIdx)
	{
		averageChannelValue += channels[channelIdx];
	}

	return averageChannelValue / channels.size();
}