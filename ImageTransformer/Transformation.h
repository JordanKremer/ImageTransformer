#pragma once
#include "Data.h"
#include <memory.h>
class Transformation
{
public:
	virtual Data transform(Data imageData) = 0;
};

