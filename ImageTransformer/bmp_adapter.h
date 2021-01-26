/*
Author : Jordan Kremer
11/20/20
bmp_adapter.h

Adapts unsigned char byte vector values to a generic_image object with a BmpHeader and pixel vector. Adapts from a generic_image
object to unsigned char byte vector values to be written to file.
*/

#pragma once
#include "Adapter.h"
#include "pixel.h"
#include <memory>


class bmp_adapter :
	public Adapter
{
public:
	std::unique_ptr<generic_image> adapt_from_raw(std::vector<unsigned char>& raw_image_values) override;
	const std::vector<unsigned char> adapt_to_raw(std::unique_ptr<generic_image> gen_image) override;

private:
	std::unique_ptr<generic_image> load_pixels(std::vector<unsigned char>& raw_image_values, std::unique_ptr<bmp_header_info> header); //can only pass unique by ref or by func(move(ptr))
	pixel build_bmp_pixel(std::vector<unsigned char>& raw_image_values, const int pixel_channel_count, int idx);
	//Padding are the extra bytes at the end of a line to make sure the horizontal line fits the bmp format
	static const int get_padding(const uint32_t bits_per_pixel, const uint32_t width);
	//channels are color channels within the pixel, e.g. a 32bit bmp pixel will have 4 channels (RGBA)
	const int get_channel_count(const int bits_per_pixel);
	
};
