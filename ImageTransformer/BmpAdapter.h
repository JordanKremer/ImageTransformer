#pragma once
#include "Adapter.h"


class BmpAdapter :
	public Adapter
{
public:
	std::shared_ptr<Data> Adapt(std::vector<unsigned char>& data);

};

