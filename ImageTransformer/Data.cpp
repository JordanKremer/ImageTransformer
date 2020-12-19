/*
Author : Jordan Kremer
11/20/20
Data.cpp

Implementation of Data.h, consisting of getters for the various important data points.

*/


#pragma once
#include "Data.h"

//https://www.fluentcpp.com/2017/09/08/make-polymorphic-copy-modern-cpp/
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



