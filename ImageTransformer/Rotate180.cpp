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


#include "rotate180.h"

std::vector<pixel> rotate180::transform_pixels(std::vector<pixel> pixels)
{
	//hdr is pulled from the abstract base transformation class
	auto hdr = get_header();
	
	if (!hdr) {
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS(): FAILED TO SET HEADER");
	}
		
	uint32_t imageWidth = hdr->get_width();
	uint32_t imageHeight = hdr->get_height();

	if (imageHeight * imageWidth > pixels.size())
		throw std::runtime_error("ERROR | ROTATE180.TRANSFORMPIXELS(): INVALID IMAGE DIMENSIONS, CANNOT TRANSFORM");
	std::reverse(pixels.begin(), pixels.end());
	return pixels;
}



//Nothing changes dimension or otherwise for the header for this transformation
std::unique_ptr<header_info> rotate180::transform_header(std::unique_ptr<header_info> hdr)
{
	//No op function
	return std::move(hdr);
}



