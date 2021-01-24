/*
Author : Jordan Kremer
1/24/2021
CellShade.h

*/


#pragma once
#include "Transformation.h"
class CellShade :
    public Transformation
{
public:
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);

private:
    //Rounds pixel values for CellShade algorithm
    void RoundPixel(Pixel& toRound);
    int RoundChannel(int channelValue);

};

