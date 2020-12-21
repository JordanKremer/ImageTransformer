/*
Author : Jordan Kremer
11/20/20
Transformation.h

This class is an interface class wherein Transformation subclasses such
as Gaussian blur and Pixelate will derive from.
*/

#pragma once
#include "Pixel.h"
#include "HeaderTransformationChanges.h"
#include <memory.h>
class Transformation
{
public:
	//Unique_ptr obj is destroyed within the function and a new one is created
	//with the transformed Data, as a new Data obj
	virtual std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels) = 0;
	virtual std::shared_ptr<HeaderTransformationChanges> GetHeaderTransformationChanges() = 0;

private:
	std::shared_ptr<HeaderTransformationChanges> _headerTransformationChanges;
};

