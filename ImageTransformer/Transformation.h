/*
Author : Jordan Kremer
11/20/20
transformation.h

This class is an interface class wherein transformation subclasses such as Gaussian blur will derive from.
*/

#pragma once
#include "pixel.h"
#include "header_info.h"
#include <memory>
#include <stdexcept>


class transformation
{
	friend class applicator;

public:
	transformation() { hdr_ = nullptr; }
	virtual ~transformation() = default;
	
	virtual std::vector<pixel> transform_pixels(std::vector<pixel> pixels) = 0;
	virtual std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr) = 0;
	
	void set_header(const header_info* to_set) { hdr_ = to_set; }
	_NODISCARD const header_info* get_header() const { return hdr_; }

	//Gives the coordinate within the pixel vector that the transformation is operating on.
	_NODISCARD uint32_t get_coordinate(int x, int y) const
	{
		const auto width = hdr_->get_width();
		return  width * y + x;
	}


private:
	//This is useful to get information such as height, width, etc, of image
	const header_info* hdr_;

};

