#pragma once
#include "Data.h"
#include <vector>
#include <memory>
class Adapter
{
public:
	virtual std::shared_ptr<Data> Adapt(std::vector<unsigned char>& data) = 0;
};

