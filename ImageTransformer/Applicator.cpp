#include "Applicator.h"
#include "HeaderInfo.h"

std::unique_ptr<Data> Applicator::ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer)
{
	//image is friend to applicator, so it's variables are directly accessible
	const HeaderInfo* hdr = image->_header.get();
	image->_pixels = transformer->TransformPixels(image->_pixels, hdr);
	image->_header = transformer->TransformHeader(std::move(image->_header));




	return std::move(image);
}
