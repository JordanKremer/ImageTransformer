#include "Applicator.h"
#include "HeaderInfo.h"

std::unique_ptr<Data> Applicator::ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer)
{
	//image is friend to applicator, so it's variables are directly accessible
	const HeaderInfo* hdr = image->_header.get();

	try {
		image->_pixels = transformer->TransformPixels(image->_pixels, hdr);
		image->_header = transformer->TransformHeader(std::move(image->_header));
	}
	catch (const std::out_of_range& error)
	{
		throw error;
	}
	catch (const std::runtime_error& error2)
	{
		throw error2;
	}
	catch (...)
	{
		return std::move(image);
	}

	return std::move(image);
}
