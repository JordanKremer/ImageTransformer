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
std::unique_ptr<generic_image> bmp_adapter::adapt_from_raw(std::vector<unsigned char>& raw_image_values)
{
	if (!(raw_image_values[0] == 'B' && raw_image_values[1] == 'M'))
	{
		throw std::runtime_error("ERROR: NOT A BMP");
	}

	if (raw_image_values.size() < 54)
	{
		throw std::runtime_error("ERROR: HEADER TOO SMALL");
	}

	bmp_header_factory fac;
	auto bmp_header = fac.get_bmp_header(raw_image_values);

	return load_pixels(raw_image_values, std::move(bmp_header));
}



//Adapts image data to raw format, by calling BuildRawDataVector
//to concat and return the header and pixels
//either pass by ref or use move to pass the unique ptr in
const std::vector<unsigned char> bmp_adapter::adapt_to_raw(std::unique_ptr<generic_image> gen_image)
{
	auto header = gen_image->get_raw_header_read_only();
	auto pixels = gen_image->get_pixels_read_only();
	if (pixels.empty())
	{
		throw std::runtime_error("ERROR: pixel vector has no data");
	}

	std::vector<unsigned char> raw_image_values;
	const auto pixelChannelCount = pixels[0].get_channel_count();
	const auto reserve_size = header.size() + (pixelChannelCount * pixels.size());
	raw_image_values.reserve(reserve_size);

	for (auto& x : header)
	{
		raw_image_values.push_back(x);
	}

	//there may be a faster method, possibly by parallelizing
	for (auto& pixel : pixels) {
		for (const auto& channel : pixel.get_all_channel_data()) {
			raw_image_values.push_back(channel);
		}
	}

	return raw_image_values;
}



//load pixels from raw data vector into a vector of pixels, taking head of the line padding
//unique ptrs must be passed by ref or by func(move(ptr))
std::unique_ptr<generic_image> bmp_adapter::load_pixels(std::vector<unsigned char>& raw_image_values, std::unique_ptr<bmp_header_info> header)
{
	std::vector<pixel> pixels;
	pixels.reserve(int64_t(header->get_width()) * header->get_height()); 	//cast to 8 byte to avoid overflow

	const auto padding = get_padding(header->get_bits_per_pixel(), header->get_width());
	const auto start_of_image = header->get_image_start_offset();
	const auto channel_count = get_channel_count(header->get_bits_per_pixel());
	const auto bits_per_line = header->get_bits_per_pixel() * header->get_width();
	int bit_count = 0;

	for(int idx = start_of_image; idx < raw_image_values.size(); idx += channel_count)
	{
		//if we are at the end of the line, ignore the padding
		if (bit_count == bits_per_line)
		{
			idx += padding;
			if (idx >= raw_image_values.size()-1)
				break;
			bit_count = 0;
		}

		pixels.push_back(build_bmp_pixel(raw_image_values, channel_count, idx));
		bit_count += channel_count;
	}

	return std::make_unique<generic_image>(raw_image_values, pixels, std::move(header));
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


