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


#include "../Headers/bmp_header_info.h"
#include <stdexcept>



bmp_header_info::bmp_header_info()
{
	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();

	bmp_header_components_->file_size = 0;
	bmp_header_components_->image_start_offset = 0;
	bmp_header_components_->width = 0;
	bmp_header_components_->height = 0;
	bmp_header_components_->bits_per_pixel = 0;
	bmp_header_components_->compression = 0;
	bmp_header_components_->horizontal_resolution = 0;
	bmp_header_components_->vertical_resolution = 0;
}


//First checks if Header is of correct size for a Bmp header, given 
//the standard formats for Bmp images.
bmp_header_info::bmp_header_info(const std::vector<unsigned char>& raw_image_values)
{
	
	if (raw_image_values.size() < 54) {
		std::string msg = "ERROR: HEADER DATA IS TOO SMALL:: SIZE: " + raw_image_values.size();
		throw std::length_error(msg);
	}

	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();

	bmp_header_components_->file_size = header_components_constructor_helper(bmp_constants::file_size, bmp_constants::reserved1, raw_image_values);
	bmp_header_components_->image_start_offset = header_components_constructor_helper(bmp_constants::image_start_offset, bmp_constants::header_size, raw_image_values);
	bmp_header_components_->width = header_components_constructor_helper(bmp_constants::width, bmp_constants::height, raw_image_values);
	bmp_header_components_->height = header_components_constructor_helper(bmp_constants::height, bmp_constants::color_panes, raw_image_values);
	bmp_header_components_->bits_per_pixel = header_components_constructor_helper(bmp_constants::bits_per_pixel, bmp_constants::compression, raw_image_values);
	bmp_header_components_->compression = header_components_constructor_helper(bmp_constants::compression, bmp_constants::image_size, raw_image_values);
	bmp_header_components_->horizontal_resolution = header_components_constructor_helper(bmp_constants::horizontal_resolution, bmp_constants::vertical_resolution, raw_image_values);
	bmp_header_components_->vertical_resolution = header_components_constructor_helper(bmp_constants::vertical_resolution, bmp_constants::num_colors_in_palette, raw_image_values);

	raw_image_values_.reserve(54);

	for (int i = 0; i < 54; ++i)
	{
		raw_image_values_.push_back(raw_image_values[i]);
	}
}


//Converts unsigned char bytes of the raw_image_values_ into usable integer components that
//can be easily read
uint32_t bmp_header_info::header_components_constructor_helper(const int bmp_constant_start, const int bmp_constant_end, const std::vector<unsigned char>& raw_image_values)
{
	uint32_t tmpCharToIntConversion = 0;
	int loadIdx = 0;
	for (int dataIdx = bmp_constant_start; dataIdx < bmp_constant_end; ++dataIdx)
	{
		((unsigned char*)& tmpCharToIntConversion)[loadIdx] = raw_image_values[dataIdx];
		++loadIdx;
	}
	return tmpCharToIntConversion;
}

void bmp_header_info::header_raw_image_data_setter_from_integer_helper(uint32_t data_to_change_to, const int bmp_constant_start, const int bmp_constant_end, std::vector<unsigned char>& raw_image_values)
{
	bmp_constants con;
	int loadIdx = 0;
	for (int dataIdx = bmp_constant_start; dataIdx < bmp_constant_end; ++dataIdx)
	{
		raw_image_values[dataIdx] = ((unsigned char*)& data_to_change_to)[loadIdx];
		++loadIdx;
	}
}


//Copy constructor
bmp_header_info::bmp_header_info(const bmp_header_info& to_copy)
{
	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();
	bmp_header_components_->id = to_copy.bmp_header_components_->id;
	bmp_header_components_->file_size = to_copy.bmp_header_components_->file_size;
	bmp_header_components_->image_start_offset = to_copy.bmp_header_components_->image_start_offset;
	bmp_header_components_->width = to_copy.bmp_header_components_->width;
	bmp_header_components_->height = to_copy.bmp_header_components_->height;
	bmp_header_components_->bits_per_pixel = to_copy.bmp_header_components_->bits_per_pixel;
	bmp_header_components_->compression = to_copy.bmp_header_components_->compression;
	bmp_header_components_->vertical_resolution = to_copy.bmp_header_components_->vertical_resolution;
	bmp_header_components_->horizontal_resolution = to_copy.bmp_header_components_->horizontal_resolution;

	raw_image_values_ = to_copy.raw_image_values_;
}




bmp_header_info& bmp_header_info::operator=(const bmp_header_info& to_copy)
{
	if (this == &to_copy)
		return *this;

	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();
	bmp_header_components_->id = to_copy.bmp_header_components_->id;
	bmp_header_components_->file_size = to_copy.bmp_header_components_->file_size;
	bmp_header_components_->image_start_offset = to_copy.bmp_header_components_->image_start_offset;
	bmp_header_components_->width = to_copy.bmp_header_components_->width;
	bmp_header_components_->height = to_copy.bmp_header_components_->height;
	bmp_header_components_->bits_per_pixel = to_copy.bmp_header_components_->bits_per_pixel;
	bmp_header_components_->compression = to_copy.bmp_header_components_->compression;
	bmp_header_components_->vertical_resolution = to_copy.bmp_header_components_->vertical_resolution;
	bmp_header_components_->horizontal_resolution = to_copy.bmp_header_components_->horizontal_resolution;

	return *this;
}



bool bmp_header_info::is_equal(const bmp_header_info& to_compare)
{
	//TODO
	return false;
}


uint32_t bmp_header_info::get_width() const
{
	return bmp_header_components_->width;
}



uint32_t bmp_header_info::get_height() const
{
	return bmp_header_components_->height;
}



uint32_t bmp_header_info::get_compression() const
{
	return bmp_header_components_->compression;
}



uint32_t bmp_header_info::get_bits_per_pixel() const
{
	return bmp_header_components_->bits_per_pixel;
}



uint32_t bmp_header_info::get_image_start_offset() const
{
	return bmp_header_components_->image_start_offset;
}



std::vector<unsigned char> bmp_header_info::get_raw_header() const
{
	return raw_image_values_;
}




void bmp_header_info::set_height(int new_height)
{
	//set bmp_header_components_ and raw_image_values_
	bmp_constants con;
	bmp_header_components_->height = new_height;
    header_raw_image_data_setter_from_integer_helper(new_height, con.height, con.height+4, raw_image_values_);
	
}



void bmp_header_info::set_width(int new_width)
{
	//set bmp_header_components_ and raw_image_values_
	bmp_constants con;

	bmp_header_components_->width = new_width;
	header_raw_image_data_setter_from_integer_helper(new_width, con.width, con.width + 4, raw_image_values_);
}
