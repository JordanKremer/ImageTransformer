#pragma once
#include "Data.h"
#include <vector>
#include <memory>
class Adapter
{
public:
	virtual std::unique_ptr<Data> AdaptFromRaw(std::vector<unsigned char>& data) = 0;
	virtual std::vector<unsigned char> AdapterToRaw(std::unique_ptr<Data> data) = 0;
};

