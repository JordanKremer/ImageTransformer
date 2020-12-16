#pragma once
#include "Transformation.h"
class Pixelate :
	public Transformation
{
public:
	Pixelate();
	std::unique_ptr<Data> Transform(std::unique_ptr<Data> adaptedData);
};


