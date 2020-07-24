#pragma once
#include "Transformation.h"
class OpenCVGaussian :
	public Transformation
{
public:
	OpenCVGaussian();
	Data transform(Data imageData);
};

