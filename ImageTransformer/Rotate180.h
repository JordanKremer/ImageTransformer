#pragma once
#include "Transformation.h"

class Rotate180 :
	public Transformation
{
public:
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header);
private:
	void Swap(std::vector<Pixel>& pixels, uint32_t pixelIdxToSwap, int curPixelIdx);

};

