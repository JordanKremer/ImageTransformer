/*
Author : Jordan Kremer
11/20/20
transformation_factory.h

This class is used to produce the inteded transformation type. Transformations include
gaussian blur, pixelation, and others. 

*/

#pragma once
#include <memory>
#include <string>
#include "generic_image.h"
#include "transformation.h"
class transformation_factory
{
public:
	std::unique_ptr<transformation> get_transformation(std::string transformation_type);

};

