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


#include "scale_up.h"

std::vector<pixel> scale_up::transform_pixels(std::vector<pixel> pixels)
{
    auto Width = get_header()->get_width();
    auto Height = get_header()->get_height();
    
    std::vector<pixel> scaledImagePixels;
    std::vector<pixel> tmpPixelHorizontalLineHolder;


    scaledImagePixels.reserve(pixels.size() * 2);
    tmpPixelHorizontalLineHolder.reserve(Width);
    

    uint32_t curPixelIdx = 0;
    //std::vector<pixel>::iterator lineStart = pixels.begin();
    uint32_t lineStart = 0;
    uint32_t prevLineStart = 0;

    //How do I update lineStart?
    //Everytime we reach width

    for (auto& p : pixels)
    {
        //if we have reached a new horizontal line
        if ((curPixelIdx + 1) % Width == 0)
        {
            lineStart = curPixelIdx; //This will set lineStart back to the beginning of the horizontal line
            for (int i = prevLineStart; i < (Width * scalar_); ++i)
            {
                auto tmpPix = scaledImagePixels[i];
                scaledImagePixels.push_back(tmpPix);
            }
        }
        

        for (int i = 0; i < scalar_; ++i)
        {
            scaledImagePixels.push_back(p);
            //tmpPixelHorizontalLineHolder.push_back(p);   //somehow account for re writing over pixels so we only have 1 width worth 
            //at most at all times in the tmp holder, if this is how we decide to do it
        }

        ++curPixelIdx;
    }

    return scaledImagePixels;
}



std::unique_ptr<header_info> scale_up::transform_header(std::unique_ptr<header_info> hdr)
{
    hdr->set_width(hdr->get_width() * scalar_);
    hdr->set_height(hdr->get_height() * scalar_);

    //set image size
    //set file size


    return std::move(hdr);
}
