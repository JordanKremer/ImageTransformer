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



#pragma once
#include "generic_image.h"

generic_image::generic_image(std::vector<unsigned char>& data, std::vector<pixel>& pixels, std::unique_ptr<header_info> header) 
{
	pixels_ = pixels;
	header_ = std::move(header);
}



generic_image::~generic_image()
{
	//delete header_;
}


const int generic_image::get_compression() const 
{
	const int c = header_->get_compression();
	return c;
}



const std::vector<unsigned char> generic_image::get_raw_header_read_only() const
{
	return header_->get_raw_header();
}



const std::vector<pixel> generic_image::get_pixels_read_only() const
{
	return pixels_;
}



