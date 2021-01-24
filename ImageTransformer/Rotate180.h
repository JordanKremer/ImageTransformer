/*
Author : Jordan Kremer
1/24/2021
Rotate180.h

Rotates iamge 180 degress.

*/

#pragma once
#include "Transformation.h"

class Rotate180 :
	public Transformation
{
public:
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo>);

};

