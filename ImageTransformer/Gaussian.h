#pragma once
#include "Transformation.h"

class Gaussian :
	public Transformation
{
public:
	Gaussian();
	Data transform(Data imageData);
};

