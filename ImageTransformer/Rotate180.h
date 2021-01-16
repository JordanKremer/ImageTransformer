#pragma once
#include "Transformation.h"

class Rotate180 :
	public Transformation
{
public:
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo>);

};

