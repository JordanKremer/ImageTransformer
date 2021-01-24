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