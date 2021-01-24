/*
Author : Jordan Kremer
1/24/2021
GaussianBlur.h

Contains functionality to perform GaussianBlur algorithm on a Pixel vector.
*/


#pragma once
#include "Transformation.h"
class GaussianBlur :
    public Transformation
{
public:
    std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
    std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> hdr);

private:
    //Wrapper function that calls the following helper functions 
    void BlurPixels(std::vector<Pixel>& pixels);
    //Utilizes the _gaussianMatrix to perform the GaussianBlur algorithm
    void PixelGridMultiply(std::vector<Pixel>& pixels, int32_t centerX, int32_t centerY);
    //Gaussian Blur does calculations within a grid, so these following Get functions
    //Help find the edges of the grid in relation to width and height of the image
    int GetXLeft(std::vector<Pixel>& pixels, int32_t centerX);
    int GetXRight(std::vector<Pixel>& pixels, int32_t centerX);
    int GetYUp(std::vector<Pixel>& pixels, int32_t centerY);
    int GetYDown(std::vector<Pixel>& pixels, int32_t centerY);
    // Returns offset from the center of the gaussian block
    int ReturnOffset(int y);
    //Returns a number from the _gaussianMatrix
    double GetGaussianNum(int x, int y);
   
    
    std::vector<unsigned char> _gaussianVector;
    double _gaussianMatrix[5][5] = {1, 4, 6, 4, 1,
                                    4, 16, 24, 16, 4,
                                    6, 24, 36, 24, 6,
                                    4, 16, 24, 16, 4,
                                    1, 4, 6, 4, 1 };
};

