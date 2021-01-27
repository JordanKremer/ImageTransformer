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



#include "../Headers/cell_shade.h"

std::vector<pixel> cell_shade::transform_pixels(std::vector<pixel> pixels)
{
	auto Width = get_header()->get_width();
	auto Height = get_header()->get_height();

	for (uint32_t x = 0; x < Width; x++)
	{
		for (uint32_t y = 0; y < Height; y++)
		{
			round_pixel(pixels[get_coordinate(x, y)]);
		}
	}

	return pixels;
}



std::unique_ptr<header_info> cell_shade::transform_header(std::unique_ptr<header_info> hdr)
{
	//no op
    return std::move(hdr);
}




void cell_shade::round_pixel(pixel& to_round)
{
	int channelIdx = 0;
	for (auto& channelValue : to_round.get_all_channel_data())
	{
		to_round.set_channel(channelIdx, round_channel(channelValue));
		++channelIdx;
	}
}



int cell_shade::round_channel(int channel_value)
{
	if ((channel_value) < 128)
	{
		if (channel_value < 64)
			return 0;
		else
			return 128;
	}
	else
	{
		if (channel_value < 192)
			return 128;
		else
			return 255;
	}
}
