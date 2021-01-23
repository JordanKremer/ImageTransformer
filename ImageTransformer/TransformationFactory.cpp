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
#include "Pixelate.h"
#include "Rotate180.h"



std::unique_ptr<Transformation> TransformationFactory::GetTransformation(std::string transformationType) {
	if (transformationType == "")
		throw std::runtime_error("ERROR | TRANSFORMATIONFACTORY::GETTRANSFORMATION() : EMPTY STRING TRANSFORMATIONTYPE");

	if (transformationType == "rotate180")
	{
		return std::move(std::make_unique<Rotate180>());
	}
	else if (transformationType == "pixelate")
	{
		return std::move(std::make_unique<Pixelate>());
	}
	else {
		return nullptr;
	}

}


