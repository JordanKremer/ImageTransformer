#pragma once
#include "Adapter.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"

class BmpAdapter :
	public Adapter
{
public:
	std::shared_ptr<Data> Adapt(std::vector<unsigned char>& data);

};

