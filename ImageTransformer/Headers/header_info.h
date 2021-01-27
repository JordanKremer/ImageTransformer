/*
Author : Jordan Kremer
11/20/20
header_info.h

Abstract base class/ interface for subclasses such as BmpHeader. generic_image.h contains this class, so it
is used as a generic way to have any type of header_info, including those in future
updates.
*/

#pragma once
#include <cstdint> //for uint_32, causes an Override error without it
#include <vector>



class header_info
{
public:
	_NODISCARD virtual uint32_t get_compression() const = 0;
	_NODISCARD virtual uint32_t get_bits_per_pixel() const = 0;
	_NODISCARD virtual uint32_t get_image_start_offset() const = 0;
	_NODISCARD virtual uint32_t get_height() const = 0;
	_NODISCARD virtual uint32_t get_width() const = 0;
	_NODISCARD virtual std::vector<unsigned char> get_raw_header() const = 0;
	
	virtual void set_height(int newHeight) = 0;
	virtual void set_width(int newWidth) = 0;

};
