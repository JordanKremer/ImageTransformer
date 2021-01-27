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


#include "../Headers/scale_up.h"

std::vector<pixel> scale_up::transform_pixels(std::vector<pixel> pixels)
{
    const auto width = get_header()->get_width();
    const auto height = get_header()->get_height();
    
    std::vector<pixel> scaled_image_pixels;
    std::vector<pixel> tmp_pixel_horizontal_line_holder;


    scaled_image_pixels.reserve(pixels.size() * 2);
    tmp_pixel_horizontal_line_holder.reserve(width);
    

    uint32_t cur_pixel_idx = 0;
    //std::vector<pixel>::iterator lineStart = pixels.begin();
    uint32_t lineStart = 0;
    const uint32_t prev_line_start = 0;

    //How do I update lineStart?
    //Everytime we reach width

    for (auto& p : pixels)
    {
        //if we have reached a new horizontal line
        if ((cur_pixel_idx + 1) % width == 0)
        {
            lineStart = cur_pixel_idx; //This will set lineStart back to the beginning of the horizontal line
            for (int i = prev_line_start; i < (width * scalar_); ++i)
            {
                auto tmpPix = scaled_image_pixels[i];
                scaled_image_pixels.push_back(tmpPix);
            }
        }
        

        for (int i = 0; i < scalar_; ++i)
        {
            scaled_image_pixels.push_back(p);
            //tmpPixelHorizontalLineHolder.push_back(p);   //somehow account for re writing over pixels so we only have 1 width worth 
            //at most at all times in the tmp holder, if this is how we decide to do it
        }

        ++cur_pixel_idx;
    }

    return scaled_image_pixels;
}



std::unique_ptr<header_info> scale_up::transform_header(std::unique_ptr<header_info> hdr)
{
    hdr->set_width(hdr->get_width() * scalar_);
    hdr->set_height(hdr->get_height() * scalar_);

    //set image size
    //set file size


    return std::move(hdr);
}
