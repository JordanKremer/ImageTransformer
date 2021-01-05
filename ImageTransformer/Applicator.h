/*
Facade Design patter
*/

#pragma once
#include "Transformation.h"
#include "Data.h"

class Applicator
{
public:
	std::unique_ptr<Data> ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer);
};

