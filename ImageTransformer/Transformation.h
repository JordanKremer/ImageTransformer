#pragma once
#include "Data.h"
#include <memory.h>
class Transformation
{
public:
	Transformation();
	virtual Data transform(Data imageData) = 0;
};

