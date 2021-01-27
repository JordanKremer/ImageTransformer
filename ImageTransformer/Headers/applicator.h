/*
Author : Jordan Kremer
1/24/2021
applicator.h

Applies a transformation to a generic_image.
*/

#pragma once
#include "transformation.h"
#include "generic_image.h"

class applicator
{
public:
	static std::unique_ptr<generic_image> apply_transformation(std::unique_ptr<generic_image> image, std::unique_ptr<transformation> transformer);
};

