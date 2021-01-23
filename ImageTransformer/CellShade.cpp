#include "CellShade.h"

std::vector<Pixel> CellShade::TransformPixels(std::vector<Pixel> pixels)
{
	auto Width = GetHeader()->GetWidth();
	auto Height = GetHeader()->GetHeight();

	for (uint32_t x = 0; x < Width; x++)
	{
		for (uint32_t y = 0; y < Height; y++)
		{
			RoundPixel(pixels[GetCoordinate(x, y)]);
		}
	}

	return pixels;
}



std::unique_ptr<HeaderInfo> CellShade::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//no op
    return std::move(hdr);
}




void CellShade::RoundPixel(Pixel& toRound)
{
	int channelIdx = 0;
	for (auto& channelValue : toRound.GetAllChannelData())
	{
		toRound.SetChannel(channelIdx, RoundChannel(channelValue));
		++channelIdx;
	}

}



int CellShade::RoundChannel(int channelValue)
{
	if ((channelValue) < 128)
	{
		if (channelValue < 64)
			return 0;
		else
			return 128;
	}
	else
	{
		if (channelValue < 192)
			return 128;
		else
			return 255;
	}
}
