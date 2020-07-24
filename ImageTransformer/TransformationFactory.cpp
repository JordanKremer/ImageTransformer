#pragma once
#include "TransformationFactory.h"
#include "Gaussian.h"
#include "OpenCVGaussian.h"
#include "Pixelate.h"
#include "OpenCVPixelate.h"
std::shared_ptr<Transformation> TransformationFactory::getTransformation(std::string transformationType, bool openCV) {
	return NULL;
}


