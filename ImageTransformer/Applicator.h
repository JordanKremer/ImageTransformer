/*
Author : Jordan Kremer
1/24/2021
Applicator.h

Applies a Transformation to a GenericImage.
*/

#pragma once
#include "Transformation.h"
#include "Data.h"

class Applicator
{
public:
	std::unique_ptr<Data> ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer);
};

