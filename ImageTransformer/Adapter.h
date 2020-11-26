/*
Author : Jordan Kremer
11/20/2020
Adapter.h

Base class for Adapters, includes functionality to adapt to and from rawData and Data objects.
Used to illustrate the adapter pattern.
*/

#pragma once
#include "Data.h"
#include <vector>
#include <memory>
class Adapter
{
public:
	virtual std::unique_ptr<Data> AdaptFromRaw(std::vector<unsigned char>& rawData) = 0;
	virtual std::vector<unsigned char> AdapterToRaw(std::unique_ptr<Data> data) = 0;
};

