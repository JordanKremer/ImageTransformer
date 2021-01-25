/*
Author : Jordan Kremer
11/20/2020
Adapter.h

Base class for Adapters, includes functionality to adapt to and from raw_image_values_ and generic_image objects.
Used to illustrate the adapter pattern.
*/

#pragma once
#include "generic_image.h"
#include <vector>
#include <memory>
class Adapter
{
public:
	virtual std::unique_ptr<generic_image> adapt_from_raw(std::vector<unsigned char>& rawData) = 0;
	virtual const std::vector<unsigned char> adapt_to_raw(std::unique_ptr<generic_image> data) = 0;
};

