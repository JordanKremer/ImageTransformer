/*
Author : Jordan Kremer
1/24/2021
grey_scale.h

Includes functionality to perform grey_scale algorithm.
*/



#pragma once
#include "transformation.h"
class grey_scale :
    public transformation
{
public:
     std::vector<pixel> transform_pixels(std::vector<pixel> pixels) override;
     std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr) override;


private:
    void set_pixel_grey(pixel& to_grey);
    uint8_t average_rgb_values(const std::vector<unsigned char> channels);

};

