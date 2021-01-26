/*
Author : Jordan Kremer
11/20/20
generic_image.h

generic_image is a container for the header_info data and pixel vector. This generic_image object is intended
to interact with transformation objects. This class is intended as read only.

*/

#pragma once
#include <vector>
#include <memory>
#include "header_info.h"
#include "bmp_header_info.h"
#include "pixel.h"

class generic_image
{
	friend class applicator; 
	//The reason to use friend is so that applicator can have access to the data without 
	//giving the data away to just anyone who asks, and can then apply it to a transformation

public:
	generic_image(std::vector<unsigned char> &data, std::vector<pixel>& pixels, std::unique_ptr<header_info> header);
	~generic_image();

	_NODISCARD const int get_compression() const;
	_NODISCARD const std::vector<unsigned char> get_raw_header_read_only() const;
	_NODISCARD const std::vector<pixel> get_pixels_read_only() const;

private:
	
	std::unique_ptr<header_info> header_;
	std::vector<pixel> pixels_;

};
