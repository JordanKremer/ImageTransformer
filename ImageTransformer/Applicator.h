/*
Author : Jordan Kremer
1/24/2021
Applicator.h

Applies a Transformation to a GenericImage.
*/

#pragma once
#include "Transformation.h"
#include "GenericImage.h"

class Applicator
{
public:
	std::unique_ptr<GenericImage> ApplyTransformation(std::unique_ptr<GenericImage> image, std::unique_ptr<Transformation> transformer);
};

