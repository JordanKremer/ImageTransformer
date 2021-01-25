/*
Author : Jordan Kremer
11/20/2020
bmp_header_factory.h

Using the factory design pattern, this class allows for the correct BmpHeader to be
generated given our raw image data.
*/



#pragma once
#include <memory>
#include "bmp_header_info.h"
class bmp_header_factory
{
public:
	bmp_header_factory();
	//Subject to change as more subtypes become supported
	std::unique_ptr<bmp_header_info> get_bmp_header(std::vector<unsigned char>& raw_image_values);
	//Different compression values for different bmp subtypes (4, 8, 24, 32 bit bmp files)
	int get_compression(std::vector<unsigned char>& raw_image_values);

};

