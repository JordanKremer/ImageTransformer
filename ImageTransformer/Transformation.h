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
	virtual std::vector<pixel> transform_pixels(std::vector<pixel> pixels) = 0;
	virtual std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr) = 0;
	void SetHeader(const header_info* to_set) { hdr_ = to_set; }
	const header_info* get_header() { return hdr_; };

	inline uint32_t get_coordinate(int x, int y)
	{
		auto width = hdr_->get_width();
		return  width * y + x;
	}


private:
	//This is useful to get information such as height, width, etc, of image
	const header_info* hdr_;

};

