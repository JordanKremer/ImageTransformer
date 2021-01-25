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

#include "grey_scale.h"

std::vector<pixel> grey_scale::transform_pixels(std::vector<pixel> pixels)
{
	auto Width = get_header()->get_width();
	auto Height = get_header()->get_height();

	for (uint32_t x = 0; x < Width; x++)
	{
		for (uint32_t y = 0; y < Height; y++)
		{
			set_pixel_grey(pixels[get_coordinate(x, y)]);
		}
	}

	return pixels;
}




std::unique_ptr<header_info> grey_scale::transform_header(std::unique_ptr<header_info> hdr)
{
    //No op
    return std::move(hdr);
}




//Averages byte color values and sets pixel to color.
void grey_scale::set_pixel_grey(pixel& to_grey)
{
	uint8_t averageChannelValue = average_rgb_values(to_grey.get_all_channel_data());
	int channelIdx = 0;
	for (auto& channelValue : to_grey.get_all_channel_data())
	{
		to_grey.set_channel(channelIdx, averageChannelValue);
		++channelIdx;
	}
}



//Averages the channel byte data for a given pixel
//and returns that number.
uint8_t grey_scale::average_rgb_values(const std::vector<unsigned char> channels)
{
	int averageChannelValue = 0;
	for (int channelIdx = 0; channelIdx < channels.size(); ++channelIdx)
	{
		averageChannelValue += channels[channelIdx];
	}

	return averageChannelValue / channels.size();
}