#pragma once
#include "Transformation.h"

class Rotate180 :
	public Transformation
{
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
	std::shared_ptr<std::map<int, int>> GetHeaderTransformationChanges();
};

