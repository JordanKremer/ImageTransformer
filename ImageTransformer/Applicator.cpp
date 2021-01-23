#include "Applicator.h"
#include "HeaderInfo.h"

std::unique_ptr<Data> Applicator::ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer)
{
	try {
		transformer->SetHeader(image->_header.get());
		image->_pixels = transformer->TransformPixels(image->_pixels);
		image->_header = transformer->TransformHeader(std::move(image->_header));
	}
	catch (const std::out_of_range& oor)
	{
		throw oor;
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
