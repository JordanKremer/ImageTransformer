#pragma once
#include "Transformation.h"
class OpenCVPixelate :
	public Transformation
{
public:
	OpenCVPixelate();
	Data transform(Data imageData)
};

