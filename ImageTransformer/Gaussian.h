#pragma once
#include "Transformation.h"

class Gaussian :
	public Transformation
{
public:
	Gaussian();
	GenericImage transform(GenericImage imageData);
};

