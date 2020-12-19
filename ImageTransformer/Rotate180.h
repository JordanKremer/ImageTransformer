#pragma once
#include "Transformation.h"
class Rotate180 :
	public Transformation
{
	std::unique_ptr<Data> Transform(std::unique_ptr<Data> adaptedData);
};

