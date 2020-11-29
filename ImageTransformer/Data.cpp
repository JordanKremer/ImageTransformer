/*
Author : Jordan Kremer
11/20/20
Data.cpp

Implementation of Data.h, consisting of getters for the various important data points.

*/


#pragma once
#include "Data.h"

//https://www.fluentcpp.com/2017/09/08/make-polymorphic-copy-modern-cpp/
Data::Data(std::vector<unsigned char>& data, std::vector<Pixel>& pixels, const HeaderInfo* header) 
{
	//_rawData = data;
	_pixels = pixels;
	_header = header->Clone();
}

Data::~Data()
{
	delete _header;
}

const int Data::GetCompression()
{
	return _header->GetCompression();
}

const std::vector<unsigned char>& Data::GetHeader() const
{
	return _header->GetRawHeader();
}

const std::vector<Pixel>& Data::GetPixels() const
{
	return _pixels;
}



