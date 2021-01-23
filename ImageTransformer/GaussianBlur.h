#pragma once
#include "Transformation.h"
class GaussianBlur :
    public Transformation
{
public:
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);


private:
    void BlurPixels(std::vector<Pixel>& pixels);
    void PixelGridMultiply(std::vector<Pixel>& pixels, int32_t centerX, int32_t centerY);
    int GetXLeft(std::vector<Pixel>& pixels, int32_t centerX);
    int GetXRight(std::vector<Pixel>& pixels, int32_t centerX);
    int GetYUp(std::vector<Pixel>& pixels, int32_t centerY);
    int GetYDown(std::vector<Pixel>& pixels, int32_t centerY);
    int ReturnOffset(int y);
    double GetGaussianNum(int x, int y);
   
    
    
    std::vector<unsigned char> _gaussianVector;
    double _gaussianMatrix[5][5] = { 1, 4, 6, 4, 1,
                                    4, 16, 24, 16, 4,
                                    6, 24, 36, 24, 6,
                                     4, 16, 24, 16, 4,
                                     1, 4, 6, 4, 1 };
};

