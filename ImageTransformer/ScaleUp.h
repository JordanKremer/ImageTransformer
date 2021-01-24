/*
Author : Jordan Kremer
1/24/2021

Include functionality to scale an image (height and width) by a scalar coefficient.

*/

#pragma once
#include "Transformation.h"
class ScaleUp :
    public Transformation
{
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);

private:
    int _scalar = 2;
};

