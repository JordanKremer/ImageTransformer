#pragma once
#include "Transformation.h"
class Pixelate :
	public Transformation
{
public:
	Pixelate();
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header);
};


