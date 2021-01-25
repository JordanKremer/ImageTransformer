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


#include "bmp_header_info.h"
#include <stdexcept>



bmp_header_info::bmp_header_info()
{
	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();

	bmp_header_components_->_filesize = 0;
	bmp_header_components_->_imageStartOffset = 0;
	bmp_header_components_->_width = 0;
	bmp_header_components_->_height = 0;
	bmp_header_components_->_bitsPerPixel = 0;
	bmp_header_components_->_compression = 0;
	bmp_header_components_->_horizontalResolution = 0;
	bmp_header_components_->_verticalResolution = 0;
}


//First checks if Header is of correct size for a Bmp header, given 
//the standard formats for Bmp images.
bmp_header_info::bmp_header_info(const std::vector<unsigned char>& data)
{
	
	if (data.size() < 54) {
		std::string msg = "ERROR: HEADER DATA IS TOO SMALL:: SIZE: " + data.size();
		throw std::length_error(msg);
	}

	bmp_constants bmpConstants;
	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();

	bmp_header_components_->_filesize = header_components_constructor_helper(bmpConstants.FILE_SIZE, bmpConstants.RESERVED1, data);
	bmp_header_components_->_imageStartOffset = header_components_constructor_helper(bmpConstants.IMAGE_START_OFFSET, bmpConstants.HEADER_SIZE, data);
	bmp_header_components_->_width = header_components_constructor_helper(bmpConstants.WIDTH, bmpConstants.HEIGHT, data);
	bmp_header_components_->_height = header_components_constructor_helper(bmpConstants.HEIGHT, bmpConstants.COLOR_PANES, data);
	bmp_header_components_->_bitsPerPixel = header_components_constructor_helper(bmpConstants.BITS_PER_PIXEL, bmpConstants.COMPRESSION, data);
	bmp_header_components_->_compression = header_components_constructor_helper(bmpConstants.COMPRESSION, bmpConstants.IMAGE_SIZE, data);
	bmp_header_components_->_horizontalResolution = header_components_constructor_helper(bmpConstants.HORIZONTAL_RESOLUTION, bmpConstants.VERTICAL_RESOLUTION, data);
	bmp_header_components_->_verticalResolution = header_components_constructor_helper(bmpConstants.VERTICAL_RESOLUTION, bmpConstants.NUM_COLORS_IN_PALETTE, data);

	raw_image_values_.reserve(54);

	for (int i = 0; i < 54; ++i)
	{
		raw_image_values_.push_back(data[i]);
	}
}


//Converts unsigned char bytes of the raw_image_values_ into usable integer components that
//can be easily read
uint32_t bmp_header_info::header_components_constructor_helper(const int bmp_constant_start, const int bmpConstantEnd, const std::vector<unsigned char>& data)
{
	uint32_t tmpCharToIntConversion = 0;
	int loadIdx = 0;
	for (int dataIdx = bmp_constant_start; dataIdx < bmpConstantEnd; ++dataIdx)
	{
		((unsigned char*)& tmpCharToIntConversion)[loadIdx] = data[dataIdx];
		++loadIdx;
	}
	return tmpCharToIntConversion;
}

void bmp_header_info::header_raw_image_data_setter_from_integer_helper(uint32_t data_to_change_to, const int bmpConstantStart, const int bmpConstantEnd, std::vector<unsigned char>& rawData)
{
	bmp_constants con;
	int loadIdx = 0;
	for (int dataIdx = bmpConstantStart; dataIdx < bmpConstantEnd; ++dataIdx)
	{
		rawData[dataIdx] = ((unsigned char*)& data_to_change_to)[loadIdx];
		++loadIdx;
	}
}


//Copy constructor
bmp_header_info::bmp_header_info(const bmp_header_info& toCopy)
{
	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();
	bmp_header_components_->_ID = toCopy.bmp_header_components_->_ID;
	bmp_header_components_->_filesize = toCopy.bmp_header_components_->_filesize;
	bmp_header_components_->_imageStartOffset = toCopy.bmp_header_components_->_imageStartOffset;
	bmp_header_components_->_width = toCopy.bmp_header_components_->_width;
	bmp_header_components_->_height = toCopy.bmp_header_components_->_height;
	bmp_header_components_->_bitsPerPixel = toCopy.bmp_header_components_->_bitsPerPixel;
	bmp_header_components_->_compression = toCopy.bmp_header_components_->_compression;
	bmp_header_components_->_verticalResolution = toCopy.bmp_header_components_->_verticalResolution;
	bmp_header_components_->_horizontalResolution = toCopy.bmp_header_components_->_horizontalResolution;

	raw_image_values_ = toCopy.raw_image_values_;
}




bmp_header_info& bmp_header_info::operator=(const bmp_header_info& toCopy)
{
	if (this == &toCopy)
		return *this;

	bmp_header_components_ = std::make_shared<basic_bmp_header_components>();
	bmp_header_components_->_ID = toCopy.bmp_header_components_->_ID;
	bmp_header_components_->_filesize = toCopy.bmp_header_components_->_filesize;
	bmp_header_components_->_imageStartOffset = toCopy.bmp_header_components_->_imageStartOffset;
	bmp_header_components_->_width = toCopy.bmp_header_components_->_width;
	bmp_header_components_->_height = toCopy.bmp_header_components_->_height;
	bmp_header_components_->_bitsPerPixel = toCopy.bmp_header_components_->_bitsPerPixel;
	bmp_header_components_->_compression = toCopy.bmp_header_components_->_compression;
	bmp_header_components_->_verticalResolution = toCopy.bmp_header_components_->_verticalResolution;
	bmp_header_components_->_horizontalResolution = toCopy.bmp_header_components_->_horizontalResolution;

	return *this;
}



bool bmp_header_info::isEqual(const bmp_header_info& toCompare)
{
	//TODO
	return false;
}


uint32_t bmp_header_info::get_width() const
{
	return bmp_header_components_->_width;
}



uint32_t bmp_header_info::get_height() const
{
	return bmp_header_components_->_height;
}



uint32_t bmp_header_info::get_compression() const
{
	return bmp_header_components_->_compression;
}



uint32_t bmp_header_info::get_bits_per_pixel() const
{
	return bmp_header_components_->_bitsPerPixel;
}



uint32_t bmp_header_info::get_image_start_offset() const
{
	return bmp_header_components_->_imageStartOffset;
}



std::vector<unsigned char> bmp_header_info::get_raw_header() const
{
	return raw_image_values_;
}




void bmp_header_info::set_height(int new_height)
{
	//set bmp_header_components_ and raw_image_values_
	bmp_constants con;
	bmp_header_components_->_height = new_height;
    header_raw_image_data_setter_from_integer_helper(new_height, con.HEIGHT, con.HEIGHT+4, raw_image_values_);
	
}



void bmp_header_info::set_width(int new_width)
{
	//set bmp_header_components_ and raw_image_values_
	bmp_constants con;

	bmp_header_components_->_width = new_width;
	header_raw_image_data_setter_from_integer_helper(new_width, con.WIDTH, con.WIDTH + 4, raw_image_values_);
}
