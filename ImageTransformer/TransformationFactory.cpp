#pragma once
#include "TransformationFactory.h"
#include "Gaussian.h"
#include "OpenCVGaussian.h"
#include "Pixelate.h"
#include "OpenCVPixelate.h"
std::shared_ptr<Transformation> TransformationFactory::getTransformation(std::string transformationType, bool openCV) {
	if (transformationType == "Gaussian" && openCV == false) {
		return std::shared_ptr<Transformation>(new Gaussian());
	}
	else if (transformationType == "Gaussian" && openCV == true){
		return std::shared_ptr<Transformation>(new OpenCVGaussian());
	}
	else if(transformationType == "Pixelate" && openCV == false){
		return std::shared_ptr<Transformation>(new Pixelate());
	}
	else if (transformationType == "Pixelate" && openCV == true) {
		return std::shared_ptr<Transformation>(new OpenCVPixelate());
	}

}


