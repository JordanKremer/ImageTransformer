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

