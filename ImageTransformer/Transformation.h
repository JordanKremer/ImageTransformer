/*
Author : Jordan Kremer
11/20/20
Transformation.h

This class is an abstract base class wherein Transformation subclasses such
as Gaussian blur and Pixelate will derive from.
*/

#pragma once
#include "Data.h"
#include <memory.h>
class Transformation
{
public:
	virtual Data Transform(Data imageData) = 0;
};

