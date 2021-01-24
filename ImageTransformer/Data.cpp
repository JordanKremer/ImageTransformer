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
#include "Data.h"

Data::Data(std::vector<unsigned char>& data, std::vector<Pixel>& pixels, std::unique_ptr<HeaderInfo> header) 
{
	_pixels = pixels;
	_header = std::move(header);
}



Data::~Data()
{
	//delete _header;
}



const int Data::GetCompression()
{
	return _header->GetCompression();
}



const std::vector<unsigned char> Data::GetRawHeaderReadOnly() const
{
	return _header->GetRawHeader();
}



const std::vector<Pixel> Data::GetPixelsReadOnly() const
{
	return _pixels;
}



