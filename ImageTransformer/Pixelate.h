#pragma once
#include "Transformation.h"
class Pixelate :
	public Transformation
{
public:
	Pixelate();
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header)
	//std::shared_ptr<std::map<int, int>> GetHeaderTransformationChanges();
};


