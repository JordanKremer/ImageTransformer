/*
Author : Jordan Kremer
1/24/2021
GreyScale.h

Includes functionality to perform GreyScale algorithm.
*/

#pragma once
#include "Transformation.h"
class GreyScale :
    public Transformation
{
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);


private:
    void SetPixelGrey(Pixel& toGrey);
    uint8_t AverageRGBValues(const std::vector<unsigned char> channels);

};
