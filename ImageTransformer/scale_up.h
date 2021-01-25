/*
Author : Jordan Kremer
1/24/2021

Include functionality to scale an image (height and width) by a scalar coefficient.

*/

#pragma once
#include "transformation.h"
class scale_up :
    public transformation
{
    std::vector<pixel> transform_pixels(std::vector<pixel> pixels);
    std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr);

private:
    int scalar_ = 2;
};

