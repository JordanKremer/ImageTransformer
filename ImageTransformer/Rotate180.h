/*
Author : Jordan Kremer
1/24/2021
rotate180.h

Rotates iamge 180 degress.

*/

#pragma once
#include "transformation.h"

class rotate180 :
	public transformation
{
public:
	std::vector<pixel> transform_pixels(std::vector<pixel> pixels);
	std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info>);

};

