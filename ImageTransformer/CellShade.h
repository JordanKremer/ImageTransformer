#pragma once
#include "Transformation.h"
class CellShade :
    public Transformation
{
public:
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);

private:
    void RoundPixel(Pixel& toRound);
    int RoundChannel(int channelValue);

};

