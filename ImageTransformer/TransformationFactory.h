/*
Author : Jordan Kremer
11/20/20
TransformationFactory.h

This class is used to produce the inteded transformation type. Transformations include
gaussian blur, pixelation, and others. 

*/

#pragma once
#include <memory>
#include <string>
#include "Data.h"
#include "Transformation.h"
class TransformationFactory
{
	TransformationFactory();
	std::shared_ptr<Transformation> getTransformation(std::string transformationType, bool openCV);

};

/*
MAKE SINGLETON
*/
