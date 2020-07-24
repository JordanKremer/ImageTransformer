#pragma once
#include <memory>
#include <string>
#include "Data.h"

class TransformationFactory
{
	TransformationFactory();
	std::shared_ptr<Transformation> getTransformation(std::string transformationType, bool openCV);
};

