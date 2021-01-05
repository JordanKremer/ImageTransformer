/*
Author : Jordan Kremer
11/20/20
Transformation.h

This class is an interface class wherein Transformation subclasses such
as Gaussian blur and Pixelate will derive from.
*/

#pragma once
#include "Pixel.h"
#include "HeaderInfo.h"
#include <memory>
#include <map>

class Transformation
{
public:
	virtual std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels) = 0;
	virtual std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header) = 0;
	//virtual std::shared_ptr<std::map<int, int>> GetHeaderTransformationChanges() = 0;
};

