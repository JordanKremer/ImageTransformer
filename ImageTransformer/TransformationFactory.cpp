/*
Author : Jordan Kremer
11/20/20
TransformationFactory.cpp

This class is used to produce the inteded transformation type. Transformations include
gaussian blur, pixelation, and others.

*/


#pragma once
#include "TransformationFactory.h"
#include "Gaussian.h"
#include "OpenCVGaussian.h"
#include "Pixelate.h"
#include "OpenCVPixelate.h"
std::shared_ptr<Transformation> TransformationFactory::GetTransformation(std::string transformationType, bool openCV) {
	return nullptr;
}


