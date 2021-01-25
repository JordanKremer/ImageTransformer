/*
Author : Jordan Kremer
11/20/2020
Adapter.h

Base class for Adapters, includes functionality to adapt to and from rawData and GenericImage objects.
Used to illustrate the adapter pattern.
*/

#pragma once
#include "GenericImage.h"
#include <vector>
#include <memory>
class Adapter
{
public:
	virtual std::unique_ptr<GenericImage> AdaptFromRaw(std::vector<unsigned char>& rawData) = 0;
	virtual const std::vector<unsigned char> AdaptToRaw(std::unique_ptr<GenericImage> data) = 0;
};

