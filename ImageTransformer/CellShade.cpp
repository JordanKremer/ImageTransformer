/*
MIT License

Copyright(c) 2021 Jordan Kremer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/



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
