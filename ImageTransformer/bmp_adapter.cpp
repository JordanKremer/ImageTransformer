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



#include "bmp_adapter.h"
#include "generic_image.h"
#include "bmp_header_factory.h"
#include "bmp_header_info_32_bit.h"
#include <memory>
#include <stdexcept>


//Takes a byte vector and builds a generic_image object with a BmpHeader and pixel vector
std::unique_ptr<generic_image> bmp_adapter::adapt_from_raw(std::vector<unsigned char>& data)
{
	if (!(data[0] == 'B' && data[1] == 'M'))
	{
		throw std::runtime_error("ERROR: NOT A BMP");
	}

	if (data.size() < 54)
	{
		throw std::runtime_error("ERROR: HEADER TOO SMALL");
	}

	bmp_header_factory fac;
	auto bmpHeader = fac.get_bmp_header(data);
	uint32_t compression = bmpHeader->get_compression();
	uint32_t bitsPerPixel = bmpHeader->get_bits_per_pixel();

	return load_pixels(data, std::move(bmpHeader));
}



//Adapts image data to raw format, by calling BuildRawDataVector
//to concat and return the header and pixels
//either pass by ref or use move to pass the unique ptr in
const std::vector<unsigned char> bmp_adapter::adapt_to_raw(std::unique_ptr<generic_image> data)
{
	auto header = data->GetRawHeaderReadOnly();
	auto pixels = data->GetPixelsReadOnly();
	if (pixels.size() == 0)
	{
		throw std::runtime_error("ERROR: pixel vector has no data");
	}

	std::vector<unsigned char> rawData;
	const int pixelChannelCount = pixels[0].get_channel_count();
	int reserveSize = header.size() + (pixelChannelCount * pixels.size());
	rawData.reserve(reserveSize);

	for (auto& x : header)
	{
		rawData.push_back(x);
	}

	//there may be a faster method, possibly by parallelizing
	for (auto& pixel : pixels) {
		for (auto& channel : pixel.get_all_channel_data()) {
			rawData.push_back(channel);
		}
	}

	return rawData;
}



//load pixels from raw data vector into a vector of pixels, taking head of the line padding
//unique ptrs must be passed by ref or by func(move(ptr))
std::unique_ptr<generic_image> bmp_adapter::load_pixels(std::vector<unsigned char>& rawdata, std::unique_ptr<bmp_header_info> header)
{
	std::vector<pixel> pixelData;
	pixelData.reserve(int64_t(header->get_width()) * header->get_height()); 	//cast to 8 byte to avoid overflow

	const int padding = get_padding(header->get_bits_per_pixel(), header->get_width());
	const int startOfImage = header->get_image_start_offset();
	const int channelCount = get_channel_count(header->get_bits_per_pixel());
	const int bitsPerLine = header->get_bits_per_pixel() * header->get_width();
	int bitCount = 0;

	for(int idx = startOfImage; idx < rawdata.size(); idx += channelCount)
	{
		//if we are at the end of the line, ignore the padding
		if (bitCount == bitsPerLine)
		{
			idx += padding;
			if (idx >= rawdata.size()-1)
				break;
			bitCount = 0;
		}

		pixelData.push_back(build_bmp_pixel(rawdata, channelCount, idx));
		bitCount += channelCount;
	}

	return std::move(std::make_unique<generic_image>(rawdata, pixelData, std::move(header)));
}



//Bmp pixels are just byte vectors, so creating a bmp pixel is simply reading
//how many channels the bmp image has in the given format by reading the header
//and building a pixel container from the rawdata
pixel bmp_adapter::build_bmp_pixel(std::vector<unsigned char>& rawdata, const int channelCount, int idx)
{
	std::vector<unsigned char> pixelChannelData;
	for (int x = 0; x < channelCount; ++x)
	{
		//build our pixel
		pixelChannelData.push_back(rawdata[idx + x]);
	}
	pixel pixel(pixelChannelData, channelCount);
	return pixel;
}



//Padding is the left over bits required at the end of each line in a bmp image,
//when reading and writing they must be taken into account
const int bmp_adapter::get_padding(uint32_t bitsPerPixel, uint32_t width)
{
	return ((width * bitsPerPixel) % 32) / 8;
}



//Each Bmp format will have a different number of pixels, refer to
//the wiki for more information
const int bmp_adapter::get_channel_count(const int bitsPerPixel)
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


