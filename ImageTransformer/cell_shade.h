/*
Author : Jordan Kremer
1/24/2021
cell_shade.h

*/


#pragma once
#include "transformation.h"
class cell_shade :
    public transformation
{
public:
    std::vector<pixel> transform_pixels(std::vector<pixel> pixels);
    std::unique_ptr<header_info> transform_header(std::unique_ptr<header_info> hdr);

private:
    //Rounds pixel values for cell_shade algorithm
    void round_pixel(pixel& to_round);
    int round_channel(int channel_value);

};

