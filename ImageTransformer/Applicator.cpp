#include "Applicator.h"

std::unique_ptr<Data> Applicator::ApplyTransformation(std::unique_ptr<Data> image, std::unique_ptr<Transformation> transformer)
{
	//update pixel vector
	image->_pixels = transformer->TransformPixels(image->_pixels);

	/*
	//update header if needed
	auto headerChanges = transformer->GetHeaderTransformationChanges();
	if (headerChanges != nullptr)
	{
		image->_header = std::move(image->_header->Clone(headerChanges));
	}
	*/

	image->_header = 



	return std::unique_ptr<Data>();
}

/*

transformation.TransformHeader(move(header))

how do I want to handle the header data?
I don't want to get set access to just anyone
friend can't handle base class so I cant just friend transformation
i could friend the applicator class

or I could clone the header but pass in a block of arguments
via creating a class that acts as a container for the args
to make it generic


newHeader = header.clone(transformer.GetArgBlock())

where arg block is a class or vector or whatever that
contains the arguments necessary to alter header

it could be a map, where the map will be iterated through
and the key values will then update the header appropriately

arg block can be null

then can do

image.header = move(newHeader)
nothing points to old header so it theoretically should be destroyed



transformation returns function pointer?*/